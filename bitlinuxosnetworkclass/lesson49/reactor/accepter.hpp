#pragma once
#include "epoll.hpp"
#include "callback.hpp"
#include <cerrno>
void Accepter(Event &ev)
{
    // 获取新连接
    while (true)
    {
        sockaddr_in peer;
        bzero(&peer, sizeof(peer));
        socklen_t len = sizeof(peer);
        int sock = accept(ev._sock, (struct sockaddr *)&peer, &len);
        if (sock > 0)
        {
            // 正常链接建立
            std::cout << "get a new link, sock: " << sock << std::endl;
            Event new_ev;
            new_ev._sock = sock;
            new_ev.SetNoBlock();
            new_ev.R = ev.R;
            new_ev.RegisterCallBack(recv_callback, nullptr, nullptr);
            (new_ev.R)->AddEvent(new_ev, EPOLLIN | EPOLLET);
        }
        else
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                // 新连接全部读完
                break;
            }
            else if (errno == EINTR)
            {
                // 被信号中断
                continue;
            }
            else
            {
                std::cerr << "accept error" << std::endl;
                continue;
            }
        }
    }
}
