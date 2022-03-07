#include "udpClient.hpp"

int main()
{
    udpClient *client = new udpClient;
    client->initClient();
    client->startClient();
    return 0;
}