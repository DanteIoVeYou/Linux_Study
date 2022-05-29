#include "epoll.hpp"
#include "accepter.hpp"

int main()
{
  // 1.创建epoll模型
  Epoll *ep = new Epoll;
  // 2.初始化
  ep->EpollInit();
  // 3.创建监听套接字
  int listen_sock = Sock::Socket();
  Sock::Bind(listen_sock, 8081);
  Sock::Listen(listen_sock);
  // 4.监听套接字只有读事件，创建监听套接字的专属Event对象，并添加到Epoll模型中
  Event listen_ev;
  listen_ev._sock = listen_sock;
  listen_ev.SetNoBlock();
  listen_ev.R = ep;
  listen_ev.RegisterCallBack(Accepter, nullptr, nullptr);

  ep->AddEvent(listen_ev, EPOLLIN | EPOLLET);
  while (true)
  {
    ep->EventDispatch(128, 1000);
  }
  return 0;
}
