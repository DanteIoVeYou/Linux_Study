#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
class udpClient
{
public:
    udpClient()
      : _sport(8080)
    {
    }

    void initClient()
    {
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd == -1)
        {
            std::cerr << "socket create fail" << std::endl;
            exit(1);
        }
    }

    void startClient()
    {
        struct sockaddr_in udp_server;
        udp_server.sin_family = AF_INET;
        udp_server.sin_port = htons(_sport);
        udp_server.sin_addr.s_addr = inet_addr("127.0.0.1");
        for (;;)
        {
            // send data to server
            std::string send_msg;
            std::cout << "enter$ ";
            std::cin >> send_msg;
            ssize_t send_ret = sendto(_sockfd, send_msg.c_str(), strlen(send_msg.c_str()), 0, (struct sockaddr *)&udp_server, sizeof(udp_server));
            // reveive data from server
            char msg[128];
            msg[0] = '\0';
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            ssize_t s = recvfrom(_sockfd, msg, sizeof(msg) - 1, 0, (struct sockaddr *)&peer, &len);
            if (s < 0)
            {
                std::cerr << "reveive data fail" << std::endl;
                continue;
            }
            msg[s] = '\0';
            std::string msg_string = msg;
            std::cout << "server$ " << msg_string << std::endl;
        }
    }
    ~udpClient()
    {
        close(_sockfd);
    }

private:
    int _sockfd;
    int _sport;
};
