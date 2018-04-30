#include "redis_cli.h"
/*
static const char *host = "127.0.0.1";
static const char *port = "6379";*/
using namespace std;
Redis_cli::Redis_cli(const char *host, const char *port):
         tcp(host, port){}

void Redis_cli::doit()
{
  int fd = tcp.creat_connect();

  while(1)
  {
    cout << "redis >> " << flush;
    memset(buf, 0, MAXLINE);
    cin.get(buf, MAXLINE);
    cin.ignore(); // 要清除cin中残留的'\n'
    strcat(buf, "\r\n");
    //cout << buf ;
    sockets::write(fd, buf, strlen(buf));

    //cout << "read now" << endl;
    memset(buf, 0, MAXLINE);
    if(sockets::read(fd, buf, MAXLINE) != 0) // 读取内容大于缓冲大小，
    {                                        // 无法读取
      showmore(buf);
      //cout << buf;
    }
  }
}

void Redis_cli::showmore(char *buf)
{
  int i = 0;
  char *p = nullptr;
  if(buf[0] == '*')
  {
    if((p = dealnum(buf+1, &i)) == nullptr)
    {
      cout << "null" << endl;
      return ;
    }
    int j = 0;
    while(i--)
    {
      cout << ++j << ") ";
      p = showstr(p+2);
    }
  }else
    showstr(buf);
}

char* Redis_cli::showstr(char *buf)  // 显示格式化字符串
{
  char ch = buf[0];
  char *p = nullptr;
  int i = 0;

  if(buf == nullptr)
    return p;

  switch(ch)
  {
    case '+':
      cout << buf+1;
      break;
    case '-':
      cout << "(error) " << buf+1;
      break;
    case ':':
      cout << "(integer) " << buf+1;
      break;
    case '$':
      p = dealnum(buf+1, &i);
      if(i == -1)
      {
        cout << "null" << endl;
      }else{
        p += 2;
        *(p+i) = '\0';
        cout << "\"" << p << "\"" << endl;
        p = p + i;
      }
      break;
  }
  return p;
}

char* Redis_cli::dealnum(char *buf, int *k)
{
  string numstr = "";
  int i = 0;
  for(; buf[i] && buf[i] != '\r'; ++i)
  {
    numstr += buf[i];
  }
  
  *k = atoi(numstr.c_str());
  
  return buf+i;
}
