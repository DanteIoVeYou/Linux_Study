#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <fcntl.h>

void SetNoBlock(int fd) {

  int ret = fcntl(fd, F_GETFL);
  if(ret < 0) {
    std::cerr << "get fl failed" << std::endl;
    return;
  }
  fcntl(fd, F_SETFL, ret | O_NONBLOCK);

}

int main()
{
  char buffer[1024];
  SetNoBlock(0);
  while(true) {
    ssize_t ss = read(0, buffer, sizeof(buffer) - 1);
    if(ss > 0) {
      buffer[ss - 1] = 0;
      std::cout << buffer << std::endl;; 
      sleep(3);
    }
    else if(errno == EAGAIN || errno == EWOULDBLOCK) {
      std::cout << "no data" << std::endl;
      sleep(3);
      continue;
    }
    else {
      std::cerr << "read: " << ss << std::endl;
      std::cerr << "errno: " << errno << std::endl;
      std::cerr << "read error" << std::endl;
      break;
    }
  }
  return 0;
}
