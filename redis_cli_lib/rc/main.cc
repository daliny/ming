#include "redis_cli.h"
#include <string>
#include <memory>
#include <iostream>
using namespace std;

static const char *host = "127.0.0.1";
static const char *port = "6379";
int main()
{
  redis_cli redis(host, port);
  redis.connect();
  string s;
  while(1)
  {
    cout << "redis_cli>> " << flush;
    getline(cin, s);
    if(s == "quit")
      return 0;
    shared_ptr<reply> rp = redis.request(s);
    cout << "here" << endl;
    reply *p = rp->next;
    bool more = false;
    int i = 0;
    while(p)
    {
      if(more == true)
        cout << ++i << ") ";
      switch(p->type)
      {
        case '*':
          more = true;
          break;
        case '$':
          cout << "\"" << p->context << "\"" << endl;
          break;
        case '-':
          cout << "(error) " << p->context << endl;
          break;
        case ':':
          cout << "(integer) " << p->context << endl;
          break;
      }
      p = p->next;
    }
  }
}

