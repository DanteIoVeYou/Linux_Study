#pragma once 
#include "sock.hpp"
#include <sys/select.h>
namespace ns_select_server 
{
  static const uint16_t g_default_port = 8081;
  static const int SELECT_ERROR = 6;
  static const int BUFFER_SIZE = 4096;

  class SelectServer {
    public:
      SelectServer(int port = g_default_port):_listen_sock(-1), _port(port) {
        _listen_sock = ns_sock::Sock::Socket();
        ns_sock::Sock::Bind(_listen_sock, _port);
        ns_sock::Sock::Listen(_listen_sock);
        // 初始化第三方数组
        for(int i = 0; i < FD_SETSIZE; i++) {
          _fd_array[i] = -1;
        }
        // 添加listen套接字为第三方数组的第一个元素
        _fd_array[0] = _listen_sock;
      }

      ~SelectServer() {
        if(_listen_sock > 0) {
          close(_listen_sock);
        }
      }

      void Loop() {
        while(true) {
          // 设置读事件的位图
          fd_set rfds;
          FD_ZERO(&rfds); // 初始化
          int max_fd = -1; // 初始化select的第一个参数
          // 告诉内核关心的读事件是什么
          for(int i = 0; i < FD_SETSIZE; i++) {
            if(_fd_array[i] != -1) {
              FD_SET(_fd_array[i], &rfds);
              if(max_fd < _fd_array[i]) {
                max_fd = _fd_array[i];
              }
            }
          }
          // select去进行等待
          int n = select(max_fd + 1, &rfds, nullptr, nullptr, nullptr); // 直到等到某个事件就绪才返回
          // 1. 异常
          if(n < 0) {
            std::cerr << "select error" << std::endl;
            exit(SELECT_ERROR);
          }
          // 2. 没有就绪的读事件
          else if(n == 0) {
            std::cout << "timeout" << std::endl;
          }
          // 3. 有读事件就绪
          else {
            for(int i = 0; i < FD_SETSIZE; i++) {
              if(_fd_array[i] == -1) {
                continue;
              }
              else {
                // 该文件描述符未就绪
                if(!FD_ISSET(_fd_array[i], &rfds)) {
                  continue;
                }
                // 该文件描述符就绪
                else {
                  // listen套接字的读事件就绪，有新的链接到来
                  if(_fd_array[i] == _listen_sock) {
                    sockaddr_in peer;
                    bzero(&peer, sizeof(peer));
                    socklen_t len = sizeof(peer);
                    int sock = accept(_listen_sock, (struct sockaddr*)&peer, &len);
                    // 不能读数据，因为不确定有没有数据
                    // 添加到第三方数组中等待下一轮循环
                    int index = 0;
                    for(; index < FD_SETSIZE; index++) {
                      if(_fd_array[index] == -1) {
                        _fd_array[index] = sock;
                        break;
                      }
                      else {
                        continue;
                      }
                    }
                    if(index == FD_SETSIZE) {
                      // 第三方数组用完了
                      std::cerr << "select管理的文件描述符超出限制" << std::endl;
                    }
                    else {
                      // 监听套接字的一个读事件处理完
                      std::cout << "sock " << sock << " 建立链接" << std::endl;
                    }
                  }
                  // 普通套接字的读事件就绪，有数据到来
                  else {
                    Handler(_fd_array[i], i);
                  }
                }
              }
            }
          }
        }
      }

    private:
      void Handler(int sock, int i) {
        char buffer[BUFFER_SIZE] = {0};
        ssize_t size = recv(sock, buffer, sizeof(buffer) - 1, 0);
        // 1. recv失败
        if(size < 0) {
          std::cerr << "recv data error" << std::endl;
        }
        // 2. 链接关闭
        else if(size == 0) {
          std::cout << "sock: " << sock << " closed link" << std::endl;
          // 读事件处理完，fd数组中置为-1
          _fd_array[i] = -1;
          // 关闭文件描述符
          close(sock); 
        }
        // 3. 正常读取数据
        else {
          buffer[size] = '\0';
          std::cout << "sock " << sock << "# " << buffer;;
        }
      }

    private:
      int _listen_sock;
      uint16_t _port;
      int _fd_array[FD_SETSIZE];
  };
}
