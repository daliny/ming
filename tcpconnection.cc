#include "tcpconnection.h"
using namespace std;

Tcpconnection::Tcpconnection(const char *h, const char *p): 
          host(h), port(p), res(nullptr), connfd(0)
{
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM; // 只能用tcp连接，用udp连接会出错
  hints.ai_flags = 0;
  hints.ai_protocol = 0;
}

int Tcpconnection::creat_connect()
{
  sockets::getaddrinfo(host, port, &hints, &res);
  struct addrinfo *rp;
  for(rp = res; rp != nullptr; rp = rp->ai_next)
  {
    connfd = sockets::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if(connfd == -1)
      continue;
    if(sockets::connect(connfd, rp->ai_addr, rp->ai_addrlen) != -1)
      break;
    sockets::close(connfd);
  }

  if(rp == nullptr)
  {
    cerr << "Connect fail" << endl;
    exit(1);
  }

  sockets::freeaddrinfo(res);

  return connfd;
}
Tcpconnection::~Tcpconnection()
{
  sockets::close(connfd);
}
