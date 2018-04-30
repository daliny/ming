#include "redis_cli.h"

using namespace std;

reply::reply():type(0), context(""), next(nullptr){}

redis_cli::redis_cli(const char *host, const char *port):tcp(host, port)
{
  memset(buf, 0, MAXLINE);
}

redis_cli::~redis_cli(){}

void redis_cli::connect()
{
  tcp.connect();
}

shared_ptr<reply> redis_cli::request(string& str)
{
  int size = str.size()-1;
  int fd = tcp.getconnfd(); // 获取连接描述符
  if(str[size] == '\n') str.erase(str.end()-1); // 若str中最后一个为换行,删除
  memset(buf, 0, MAXLINE); // 清空
  strcpy(buf, str.c_str());
  strcat(buf, "\r\n");
  sockets::write(fd, buf, strlen(buf)); // 发送请求
  memset(buf, 0, MAXLINE); // 清空
  sockets::read(fd, buf, MAXLINE); // 响应数据大于MAXLINE部分读取不到，需改！！
  //cout << buf << endl;
  return dealAllStr();
}

shared_ptr<reply> redis_cli::dealAllStr()
{
  reply *rp = new reply();
  reply *np = rp;

  posp = buf;
  while(*posp)
  {
    if(np == nullptr)
      np = new reply();
    dealStr(np, posp[0]);
    np = np->next;
  }

  return shared_ptr<reply>(rp, [](reply* p){
                        reply* n = p;
                        while(n)
                        {
                         // cerr << "delete" << endl;
                          p = p->next;
                          delete n;
                          n = p;
                        }
                    });
}

void redis_cli::dealStr(reply *p, char type)  
  // 内容存放到p, 
{
  posp += 1;
  //*ptr = new reply();
  p->type = type;
  
  int length = 0;
  switch(type)
  {
    case '$':
      length = strtonum();  // 要改变posp到下一次访问点
      p->length = length;
      if(length != -1)
      {
         strcopy(p->context, length); // 要改变posp到末尾
      }
      break;

    case '*':
      p->length = strtonum();
      break;

    case '+': case '-': case ':':
      strcopy(p->context, strlen(posp)-2);
      break;
  }
}

int redis_cli::strtonum()
{
  if(posp[0] == '-')
    return -1;
  int n = 0;
  while(*posp != '\r')
  {
    n *= 10;
    n += *posp - '0';
    ++posp;
  }
  posp += 2;
  return n;
}

void redis_cli::strcopy(string& s, int length)
{
  for(int i = 0; i < length; ++i)
  {
    s += *posp;
    ++posp;
  }
  posp += 2;
}
