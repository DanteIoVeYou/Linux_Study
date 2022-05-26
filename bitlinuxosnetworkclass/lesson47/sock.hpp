#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace ns_sock {
  static const int BACKLOG = 5;
  
  enum Error {
    CREATE = 1,
    BIND,
    LISTEN
  };

  class Socket {
    public:
      Socket() {}
      ~Socket() {}
      static int CreateSocket() {
        int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
        if(listen_sock < 0) {
          std::cerr << "create sock error" << std::endl;
          exit(CREATE);
        }
        else {
          return listen_sock;
        }
      }

      static void Bind(int listen_sock, uint16_t port) {
        sockaddr_in local;
        bzero(&local, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = INADDR_ANY;
        if(bind(listen_sock, (struct sockaddr*)&local, sizeof(local)) < 0) {
          std::cerr << "bind error" << std::endl;
          exit(BIND);
        }
      }

      static void Listen(int sock) {
        if(listen(sock, BACKLOG) < 0) {
          std::cerr << "listen error" << std::endl;
          exit(LISTEN);
        }
      }
  };
}

