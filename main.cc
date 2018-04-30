#include "redis_cli.h"

static const char *host = "127.0.0.1";
static const char *port = "6379";
int main()
{
  Redis_cli redis(host, port);
  redis.doit();
}
