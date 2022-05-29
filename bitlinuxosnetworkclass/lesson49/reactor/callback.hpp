#pragma once
#include <iostream>
#include "epoll.hpp"

void recv_callback(Event &ev)
{
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