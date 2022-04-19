#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <fstream>
#include <cstring>

#define SRC_PATH "wwwroot/index.html"
#define NOTFOUND "wwwroot/13-404-rolling-box.html"
namespace srv
{
    class httpServer
    {
    public:
        httpServer(uint16_t port) : _port(port), _listen_sock(-1) {}
        ~httpServer() { close(_listen_sock); }
        static void *handler(void *args)
        {
            // 线程分离
            pthread_detach(pthread_self());
            // 接受请求
            int sock = *(int *)args;
            delete (int *)args;
            char buffer[4096] = {0};
            ssize_t s = recv(sock, buffer, sizeof(buffer) - 1, 0);
            if (s < 0)
            {
                std::cerr << "recv failed." << std::endl;
                return nullptr;
            }
            else
            {
                std::cout << "====================================================" << std::endl;
                buffer[s] = 0;
                std::cout << buffer;
                std::cout << "====================================================" << std::endl;
            }
            // 做出响应
            // 返回http报头 + 网页
            // std::string body = "<html><body><h1>HELLOWORLD</h1></body></html>";
            std::string body;
            std::string line;
            std::ifstream in("wwwroot/index.html", std::ios::in | std::ios::binary);
            // std::ifstream in(SRC_PATH);
            if (in.is_open())
            {
                while (std::getline(in, line))
                {
                    body += line;
                }
            }
            else
            {
                std::ifstream in(NOTFOUND);
                while (std::getline(in, line))
                {
                    body += line;
                }
            }

            std::string resp;
            // 1. 状态行： http版本 + 状态码 + 状态码描述
            resp += "HTTP/1.1 200 OK\n";
            // 2. 响应报头：数据类型
            resp += "Contect-Type: text/html\n";
            // 3. 响应报头：Body的长度
            resp += "Content-Length: " + std::to_string(body.size()) + "\n";
            // 4. 空行
            resp += "\n";
            // 5. 响应正文
            resp += body;
            ssize_t ss = send(sock, resp.c_str(), resp.size(), 0);
            if (ss < 0)
            {
                std::cerr << "send failed" << std::endl;
                return nullptr;
            }
            close(sock);
            return nullptr;
        }
        void init()
        {
            // 1. 创建套接字
            _listen_sock = socket(AF_INET, SOCK_STREAM, 0);
            if (_listen_sock < 0)
            {
                std::cerr << "create socket failed." << std::endl;
                exit(1);
            }
            // 2.绑定套接字
            sockaddr_in local;
            memset(&local, 0, sizeof(local));
            local.sin_family = AF_INET;
            local.sin_port = htons(_port);
            local.sin_addr.s_addr = INADDR_ANY;
            if (bind(_listen_sock, (sockaddr *)&local, sizeof(local)) < 0)
            {
                std::cerr << "bind failed." << std::endl;
                exit(2);
            }
            // 3.监听套接字
            listen(_listen_sock, 5);
        }

        void start()
        {
            while (true)
            {
                sockaddr_in peer;
                memset(&peer, 0, sizeof(peer));
                socklen_t len = sizeof(peer);
                int sock = accept(_listen_sock, (sockaddr *)&peer, &len);
                if (sock < 0)
                {
                    std::cerr << "accept fail." << std::endl;
                    continue;
                }
                // 建立链接，创建线程处理
                pthread_t tid;
                int *psock = new int(sock);
                pthread_create(&tid, nullptr, handler, psock);
            }
        }

    private:
        uint16_t _port;
        int _listen_sock;
    };
} // namespace end