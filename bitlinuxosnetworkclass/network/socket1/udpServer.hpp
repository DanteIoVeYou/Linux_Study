#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
class udpServer
{
public:
    udpServer(int port = 8080)
      :_port(port)
    {
    }

    void initServer()
    {
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd == -1)
        {
            std::cerr << "socket create fail" << std::endl;
            exit(1);
        }
        struct sockaddr_in local;
        local.sin_family = AF_INET;
        local.sin_port = htons(_port);
        local.sin_addr.s_addr = INADDR_ANY;
        if (bind(_sockfd, (struct sockaddr *)&local, sizeof(local)) < 0)
        {
            std::cerr << "bind wrong" << std::endl;
            exit(2);
        }
        else
        {
            std::cout << "bind success" << std::endl;
        }
    }

    void startServer()
    {
        char msg[128];
        for (;;)
        {
            // reveive data from peer
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
            std::cout << "client$ " << msg_string << std::endl;
            // send data to peer
            std::string rv = "[echo]" + msg_string;
            ssize_t send_ret = sendto(_sockfd, rv.c_str(), strlen(rv.c_str()), 0, (struct sockaddr *)&peer, len);
        }
    }
    ~udpServer()
    {
        close(_sockfd);
    }

private:
    short _port;
    int _sockfd;
};
