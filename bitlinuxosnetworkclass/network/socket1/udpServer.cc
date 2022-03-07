#include "udpServer.hpp"

int main()
{
    udpServer *server = new udpServer;
    server->initServer();
    server->startServer();
    return 0;
}