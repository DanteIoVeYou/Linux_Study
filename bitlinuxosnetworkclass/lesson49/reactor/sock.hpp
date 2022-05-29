#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>

class Sock
{
public:
    Sock() {}
    ~Sock() {}
    static int Socket()
    {
        int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
        return listen_sock;
    }
    static void Bind(int sock, uint16_t port)
    {
        sockaddr_in local;
        bzero(&local, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = INADDR_ANY;
        int opt = 1;
        setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
        if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
        {
            exit(1);
        }
    }
    static void Listen(int sock)
    {
        listen(sock, 5);
    }
};