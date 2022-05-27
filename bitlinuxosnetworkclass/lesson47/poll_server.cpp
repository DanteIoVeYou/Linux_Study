#include "poll_server.hpp"
#include "utils.hpp"
int main(int argc, char* argv[])
{
  if(argc == 1) {
    // 默认8080端口
    ns_poll_server::PollServer *srv = new ns_poll_server::PollServer();
    srv->Loop();
  }
  else if(argc == 2) {
    // 使用自定义的端口
    ns_poll_server::PollServer *srv = new ns_poll_server::PollServer(atoi(argv[1]));
    srv->Loop();
  }
  else {
    ns_utils::Manual(argv[0]);
    return 17;
  }
  return 0;
}
