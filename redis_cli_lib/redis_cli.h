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
  void  strcopy(string& s, int length);
  int   strtonum();
  shared_ptr<reply> dealAllStr();
  void dealStr(reply *p, char type);

  Tcpconnection tcp;
  char buf[MAXLINE];
  char *posp = buf; // 在读取数据时使用，每行数据的首地址
};

#endif
