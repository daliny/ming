#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H
#include "sockets.h"
#include <string.h>

class Tcpconnection{
public:
  Tcpconnection(const char *h, const char *p);
  ~Tcpconnection();

  void connect();
  int getconnfd();
private:
  const char *host; // 服务器主机名
  const char *port; // 服务器端口
  struct addrinfo hints;
  struct addrinfo *res;
  int connfd;
};

#endif
