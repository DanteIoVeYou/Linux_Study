#pragma once
#include <iostream>
#include "epoll.hpp"
int Reader(int sock, std::string *out)
{
    while (true)
    {
        char buffer[1024] = {0};
        ssize_t size = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (size > 0)
        {
            // 正常读取
            buffer[size] = '\0';
            (*out) += buffer;
        }
        else
        {
            // 读取失败
            if (errno == EINTR)
            {
                // 信号中断
                continue;
            }
            else if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                // 因为你在非阻塞读取的状态下，不知道最后一次是否已经读完毕。那么如果最后第二次已经全部读完而你并不知道，那么就会再读一次，这一次什么也读不到，recv返回-1，errno被设置为EAGAIN/EWOULDBLOCK
                break;
            }
            else
            {
                return -1;
            }
        }
    }
    return 1;
}

int Sender(int sock)
{       
}
void recv_callback(Event &ev)
{
    // 每一个普通链接套接字的读事件
    int sock = ev._sock;
    // 非阻塞读取到event类中的缓冲区
    // 返回值
    // 1: 正常读取完毕
    // 0: 本轮读取完毕，遇到阻塞的情况
    // -1: 读取出错
    std::string str;
    int ret_code = Reader(sock, &str);
    if (ret_code == 1)
    {
        ev._inbuffer = std::move(str);
    }
    else
    {
        ev._except(ev);
    }
    std::cout << "recv" << std::endl;
}

void send_callback(Event &ev)
{
    std::cout << "send" << std::endl;
}

void except_callback(Event &ev)
{
    std::cout << "except" << std::endl;
}