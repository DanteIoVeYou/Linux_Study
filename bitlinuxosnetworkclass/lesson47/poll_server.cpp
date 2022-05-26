#include "poll_server.hpp"
int main()
{
  ns_poll_server::PollServer *srv = new ns_poll_server::PollServer(8081);
  srv->Loop();
  return 0;
}
