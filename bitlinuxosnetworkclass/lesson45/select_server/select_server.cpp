#include "select_server.hpp"

int main()
{
  ns_select_server::SelectServer *srv = new ns_select_server::SelectServer;
  srv->Loop();
  return 0;
}
