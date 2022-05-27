#include "epoll_server.hpp"
int main()
{
  ns_epoll_server::EpollServer *srv = new ns_epoll_server::EpollServer(8081);
  return 0;
}
