#include "sock.hpp"
#include <poll.h>

namespace ns_poll_server {

  static const uint16_t DEFAULT_PORT = 8080;
  static const int SOCK_NUM = 1024; 
  static const int TIMEOUT = -1;
  static const size_t BUFFER_SIZE = 4096;

  enum ERROR {
    MALLOC = 10
  };
  class PollServer {
    public:
      PollServer(uint16_t port = DEFAULT_PORT): _port(port) {
        _listen_sock = ns_sock::Socket::CreateSocket();
        ns_sock::Socket::Bind(_listen_sock, _port);
        ns_sock::Socket::Listen(_listen_sock);
        // 初始化pollfds
        // 开辟空间
        _pollfds = (struct pollfd*) malloc(sizeof(struct pollfd) * SOCK_NUM);
        if(_pollfds == nullptr) {
          std::cerr << "malloc pollfds error" << std::endl;
          exit(MALLOC);
        }
        // 置空
        for(size_t i = 0; i < SOCK_NUM; i++) {
          _pollfds[i].fd = -1;
          _pollfds[i].events = 0;
          _pollfds[i].revents = 0;
        }
        // 绑定listen_sock 到_pollfds中，并监听读事件
        _pollfds[0].fd = _listen_sock;
        _pollfds[0].events = POLLIN;
      }

      ~PollServer() {
        if(_listen_sock > 0) {
          close(_listen_sock);
        }
      }

      void Handler() {
        for(size_t i = 0; i < SOCK_NUM; i++) {
          // 当前下标的元素不是被关心的文件描述符
          if(_pollfds[i].fd == -1) {
            continue;
          }
          // 当前文件描述符被关心
          else {
            // 当前文件描述符读事件已就绪
            if(_pollfds[i].revents & POLLIN) {
              // 读就绪的文件描述符是监听套接字
              if(_pollfds[i].fd == _listen_sock) {
                // accept建立链接
                sockaddr_in peer;
                bzero(&peer, sizeof(peer));
                socklen_t len = sizeof(peer);
                int sock = accept(_listen_sock, (struct sockaddr*)&peer, &len);
                if(sock < 0) {
                  std::cerr << "accept error" << std::endl;
                  return;
                }
                else {
                  // 建立新链接成功
                  std::cout << "get a new link: " << sock << std::endl;
                  // 将新的文件描述符添加到poll中进行读事件的等待检测
                  size_t index = 0;
                  for(; index < SOCK_NUM; index++) {
                    if(_pollfds[index].fd == -1) {
                      break;
                    }
                  }
                  // 打开的文件描述符过多
                  if(index == SOCK_NUM) {
                    std::cerr << "poll fd too much error" << std::endl;
                    return;
                  }
                  // 成功添加新的文件描述符
                  else {
                    _pollfds[index].fd = sock;
                    _pollfds[index].events = POLLIN;
                    // 把监听套接字的读就绪清空
                    _pollfds[i].revents = 0;
                    _pollfds[i].events = POLLIN;
                  }
                }
              }
              // 读就绪的文件描述符是其他套接字
              else {
                //  打印数据
                char buffer[BUFFER_SIZE] = {0};
                ssize_t size = recv(_pollfds[i].fd, buffer, sizeof(buffer) - 1, 0);
                // recv失败
                if(size < 0) {
                  std::cerr << "recv error" << std::endl;
                  _pollfds[i].fd = -1;
                  _pollfds[i].events = 0;
                  _pollfds[i].revents = 0;
                  return;
                }
                // 对端链接关闭
                else if(size == 0) {
                  std::cout << "close: " << _pollfds[i].fd << std::endl;
                  // 关闭文件描述符
                  close(_pollfds[i].fd);
                  _pollfds[i].fd = -1;
                  _pollfds[i].events = 0;
                  _pollfds[i].revents = 0;
                  return;
                }
                // 成功读取数据
                else {
                  buffer[size] = '\0';
                  std::cout << "sock " << _pollfds[i].fd << ": " << buffer;
                  _pollfds[i].revents = 0;
                  _pollfds[i].events = POLLIN;
                }
              }
            }
            // 当前文件描述符未就绪读
            else {
              continue;
            }
          }
        }
      }

      void Loop() {
        while(true) {
          int n = poll(_pollfds, SOCK_NUM, TIMEOUT);
          switch(n) {
            // poll出错
            case -1:
              std::cerr << "poll error" << std::endl;
              continue;
              break;
            // 没有就绪的文件描述符
            case 0:
              std::cout << "timeout..." << std::endl;
              break;
            // 有文件描述符就绪
            default:
              Handler();
              break;
          }
        }
      }

    private:
      uint16_t _port;
      int _listen_sock; 
      struct pollfd *_pollfds;
  };
}//namespace
