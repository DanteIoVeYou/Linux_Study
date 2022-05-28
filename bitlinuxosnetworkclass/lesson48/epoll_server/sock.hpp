#pragma once 
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


namespace ns_socket {

  static const int BACKLOG = 5;
  class Socket {
    public:
      static int Create() {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0) {
          std::cerr << "socket error" << std::endl;
          exit(11);
        }
        
        return sock;
      }

      static void Bind(int listen_sock, uint16_t port) {
        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = INADDR_ANY;
        int opt = 1;
        setsockopt(listen_sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
        if(bind(listen_sock, (struct sockaddr*)&local, sizeof(local)) < 0) {
          std::cerr << "bind error" << std::endl;
          exit(12);
        }
      }

      static void Listen(int listen_sock) {
        listen(listen_sock, BACKLOG);
      }
  };
}







