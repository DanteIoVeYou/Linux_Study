#include "sock.hpp"
#include <sys/epoll.h>

namespace ns_epoll_server {

  static const size_t MAXEVENTS = 128;
  static const int TIMEOUT = -1;
  static const size_t BUFFER_SIZE = 4096;

  enum ERROR {
    EPOLL_CREATE_ERROR = 2,
    EPOLL_CTL_ERROR,
    EPOLL_WAIT_ERROR,
    ACCEPT_ERROR,
    RECV_ERROR
  };

  class EpollServer {

    public:
      EpollServer(uint16_t port): _port(port) {
        // 创建套接字
        _listen_sock = ns_socket::Socket::Create();
        // 绑定套接字
        ns_socket::Socket::Bind(_listen_sock, _port);
        // 监听套接字
        ns_socket::Socket::Listen(_listen_sock);
        
        // 创建epoll模型
        // epoll模型创建成功的返回值是对应的模型的文件描述符，epoll模型以文件的形式由内核进行管理
        _epoll_fd = epoll_create(128);
        if(_epoll_fd < 0) {
          // 创建epoll模型失败
          std::cerr << "epoll_create error" << std::endl;
          exit(EPOLL_CREATE_ERROR);
        }
        else {
          // 创建epoll模型成功
          // 向epoll模型中添加监听套接字
          struct epoll_event ev;
          ev.events = EPOLLIN;
          ev.data.fd = _listen_sock;
          epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _listen_sock, &ev);
          Loop();
        }
      }
    private:
      void Loop() {
        while(true) {
          // 初始化epoll_event数组
          _epoll_events = (struct epoll_event*)malloc(sizeof(struct epoll_event) * MAXEVENTS);
          // 等待 
          int n = epoll_wait(_epoll_fd, _epoll_events, MAXEVENTS, TIMEOUT);
          // 等待出错
          if(n == -1) {
            std::cerr << "epoll_wait error" << std::endl;
            exit(EPOLL_WAIT_ERROR);
          }
          // 等待超时
          else if(n == 0) {
            std::cout << "timeout..." << std::endl;
          }
          // 等待成功，有n个事件就绪
          else {
            for(int i = 0; i < n; i++) {
              if(_epoll_events[i].events & EPOLLIN) {
                // 读事件就绪
                if(_epoll_events[i].data.fd == _listen_sock) {
                  // 监听套接字就绪
                  struct sockaddr_in peer;
                  memset(&peer, 0, sizeof(peer));
                  socklen_t len = sizeof(peer);
                  int sock = accept(_listen_sock, (struct sockaddr*)&peer, &len);
                  if(sock < 0) {
                    std::cerr << "accept error" << std::endl;
                    exit(ACCEPT_ERROR);
                  }
                  else {
                    // 把新的套接字放入到epoll模型中，监听读事件
                    struct epoll_event ev;
                    ev.events = EPOLLIN;
                    ev.data.fd = sock;
                    epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, sock, &ev);
                    std::cout << "get a new link, sock: " << sock << std::endl;
                  }
                }
                else {
                  // 其他套接字就绪，有数据到来
                  char buffer[BUFFER_SIZE] = {0};
                  ssize_t size = recv(_epoll_events[i].data.fd, buffer, sizeof(buffer) - 1, 0);
                  if(size < 0) {
                    std::cerr << "recv error" << std::endl;
                    exit(RECV_ERROR);
                  }
                  else if(size == 0) {
                    std::cout << "close: " << _epoll_events[i].data.fd << std::endl;
                    close(_epoll_events[i].data.fd);
                    epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, _epoll_events[i].data.fd, nullptr);
                  }
                  else {
                    buffer[size] = 0;
                    std::cout << "sock " << _epoll_events[i].data.fd << "# " << buffer;
                    // 修改套接字状态，改为读事件监听与写事件监听
                    struct epoll_event ev;
                    ev.events = EPOLLIN | EPOLLOUT;
                    ev.data.fd = _epoll_events[i].data.fd;
                    epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, _epoll_events[i].data.fd, &ev);
                  }
                }
              }
              else if (_epoll_events[i].events & EPOLLOUT) {
                // 该文件描述符写事件就绪
                std::string msg = "OK!\n";
                send(_epoll_events[i].data.fd, msg.c_str(), msg.size(), 0);
                struct epoll_event ev;
                ev.events = EPOLLIN;
                ev.data.fd = _epoll_events[i].data.fd;
                epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, _epoll_events[i].data.fd, &ev);
              }
            }
          }
          free(_epoll_events);
        }
      }
    public:
      ~EpollServer() {
        if(_listen_sock > 0) {
          close(_listen_sock);
        }
        free(_epoll_events);
      }

    private:
      int _listen_sock;
      uint16_t _port;
      int _epoll_fd;
      struct epoll_event *_epoll_events;
  };
}

