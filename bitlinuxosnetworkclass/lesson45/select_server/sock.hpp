#pragma once 
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace ns_sock
{
  static const int BACKLOG = 5;

  enum {
    SOCKET_ERROR = 2,
    BIND_ERROR,
    LISTEN_ERROR,
    ACCEPT_ERROR
  };

  class Sock {
  public:
    static int Socket() {
      int sock = socket(AF_INET, SOCK_STREAM, 0);
      if(sock == -1) {
        std::cerr << "create socket failed" << std::endl;
        exit(SOCKET_ERROR);
      }
      int opt = 1;
      setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
      return sock;
    }
    
    static void Bind(int sock, uint16_t port) {
      sockaddr_in local;
      bzero(&local, sizeof(local));
      local.sin_family = AF_INET;
      local.sin_port = htons(port);
      local.sin_addr.s_addr = INADDR_ANY;
      if(bind(sock, (struct sockaddr*)&local, sizeof(local)) == -1) {
        std::cerr << "bind error" << std::endl;
        exit(BIND_ERROR);
      }
    }

    static void Listen(int sock) {
      if(listen(sock, BACKLOG) == -1) {
        std::cerr << "listen failed" << std::endl;
        exit(LISTEN_ERROR);
      }
    }

    static void Accept(){}

  };
}//ns_sock
