#ifndef REDIS_CLI_H
#define REDIS_CLI_H
#include "sockets.h"
#include "tcpconnection.h"
#include <iostream>
#include <string.h>

#define MAXLINE 1024
class Redis_cli{
public:
  Redis_cli(const char *host, const char *port);
  void doit();
private:
  char *dealnum(char *buf, int *k);
  void showmore(char *buf);
  char *showstr(char *buf);
  Tcpconnection tcp;
  char buf[MAXLINE];
};

#endif
