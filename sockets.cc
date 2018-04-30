#include "sockets.h"
using namespace std;
void sockets::close(int sockfd)
{
  if(::close(sockfd) < 0)
  {
    cerr << "sockets::close error: " << ::strerror(errno) << endl;
    exit(1);
  }
}

int sockets::socket(int domain, int type, int protocol)
{
  int fd;
  fd = ::socket(domain, type, protocol);
  //if((fd = ::socket(domain, type, protocol)) == -1)
   // cerr << "sockets::socket error: " << ::strerror(errno) << endl;
  return fd;
}

int sockets::connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
  int rc;

  rc = ::connect(sockfd, addr, addrlen);
/*
  if((rc = ::connect(sockfd, addr, addrlen)) == -1)
    cerr << "sockets::connect error: " << ::strerror(errno) << endl;
 */
  return rc;
}

void sockets::getaddrinfo(const char *host, const char *service, 
                          const struct addrinfo *hints, struct addrinfo **res)
{
  int err;

  if((err = ::getaddrinfo(host, service, hints, res)) != 0)
  {
    cerr << "sockets::getaddrinfo error: " << ::gai_strerror(err) << endl;
    exit(1);
  }
}

void sockets::freeaddrinfo(struct addrinfo *res)
{
  ::freeaddrinfo(res);
}

ssize_t sockets::read(int fd, void *buf, size_t count)
{
  int rc;
  if((rc = ::read(fd, buf, count)) == -1)
  {
    cerr << "sockets::read error: " << strerror(errno) << endl;
    exit(1);
  }
  return rc;
}

ssize_t sockets::write(int fd, const void *buf, size_t count)
{
  int rc;
  if((rc = ::write(fd, buf, count)) == -1)
  {
    cerr << "sockets::write error: " << strerror(errno) << endl;
    exit(1);
  }
  return rc;
}
