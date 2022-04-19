#include "httpServer.hpp"

int main(int argc, char *argv[])
{
    srv::httpServer srvIns(atoi(argv[1]));
    srvIns.init();
    srvIns.start();
    return 0;
}