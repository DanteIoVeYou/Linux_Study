#pragma once 
#include "sock.hpp"
namespace ns_select_server 
{
  static const uint16_t g_default_port = 8081;
  class SelectServer {
    public:
      SelectServer(int port = g_default_port):_listen_sock(-1), _port(port) {
        _listen_sock = ns_sock::Sock::Socket();
        ns_sock::Sock::Bind(_listen_sock, _port);
        ns_sock::Sock::Listen(_listen_sock);
      }

      void Loop() {
        while(1) {
          std::cout << "loop" << std::endl;
          sleep(1);
        }

      }
    private:
      int _listen_sock;
      uint16_t _port;
  };
}
