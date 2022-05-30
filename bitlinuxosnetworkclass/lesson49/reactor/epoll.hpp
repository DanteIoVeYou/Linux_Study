#pragma once
// 所有套接字读事件常打开，写事件按需打开

#include "sock.hpp"
#include <sys/epoll.h>
#include <unordered_map>
#include <fcntl.h>
// 对应的套接字封装成的一个类，保存了套接字的信息
class Event;
class Reactor;
typedef void (*CallBack)(Event &);

// 将文件描述符封装起来
class Event
{
public:
    Event() : _sock(-1) {}
    // 注册读写异常方法
    void RegisterCallBack(CallBack recv, CallBack send, CallBack except)
    {
        _recv = recv;
        _send = send;
        _except = except;
    }
    void SetNoBlock()
    {
        int fl = fcntl(_sock, F_GETFL);
        fcntl(_sock, F_SETFL, fl | O_NONBLOCK);
    }
    int _sock;
    std::string _inbuffer;
    std::string _outbuffer;
    CallBack _recv = nullptr;
    CallBack _send = nullptr;
    CallBack _except = nullptr;
    Reactor *R = nullptr;
};

// 承担了Epoll框架的责任
class Reactor
{
public:
    Reactor() {}
    ~Reactor() {}
    // 创建Epoll框架
    void ReactorInit()
    {
        _epfd = epoll_create(128);
        if (_epfd < 0)
        {
            exit(2);
        }
    }
    // 向epoll模型添加事件
    void AddEvent(Event &ev, uint32_t events)
    {
        struct epoll_event event;
        event.events = events;
        event.data.fd = ev._sock;
        if (epoll_ctl(_epfd, EPOLL_CTL_ADD, ev._sock, &event) < 0)
        {
            exit(3);
        }
        else
        {
            _sock_ev_map.insert(std::make_pair(ev._sock, ev));
        }
    }
    // 删除epoll模型关心的事件
    void DelEvent(Event &ev)
    {
    }
    // 分发事件给OS等待
    void EventDispatch(int num, int timeout)
    {
        struct epoll_event evs[num];
        int n = epoll_wait(_epfd, evs, num, timeout);
        for (int i = 0; i < n; i++)
        {
            int sock = evs[i].data.fd;
            uint32_t ev = evs[i].events;
            // 读事件就绪
            if (ev & EPOLLIN)
            {
                if (_sock_ev_map[sock]._recv)
                {
                    _sock_ev_map[sock]._recv(_sock_ev_map[sock]);
                }
            }
            if (ev & EPOLLOUT)
            {
                if (_sock_ev_map[sock]._send)
                {
                    _sock_ev_map[sock]._send(_sock_ev_map[sock]);
                }
            }
        }
    }

private:
    int _epfd;
    std::unordered_map<int, Event> _sock_ev_map;
};
