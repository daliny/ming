#ifndef REDIS_CLI_H
#define REDIS_CLI_H

#include <iostream>
#include <string>
#include <memory>
#include <string.h>
#include "tcpconnection.h"
#include "sockets.h"
#define MAXLINE 1024

using namespace std;  // 注意命名空间，用到string和shared_ptr

struct reply{
  char type; // 数据类型
  int  length; // 数据长度
  string context; // 数据内容
  reply *next;

  reply();
};

class redis_cli{
public:
  redis_cli(const char *host, const char *port);
  void connect();
  shared_ptr<reply> request(string& str);
  ~redis_cli();
private:
  void  strcopy(string& s, char *posp, int length);
  int   strtonum(char *posp);
  shared_ptr<reply> dealAllStr();
  char  *dealStr(reply *p, char *pos, char type);

  Tcpconnection tcp;
  char buf[MAXLINE];
  char *posp = buf;
};

#endif
