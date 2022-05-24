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
    }
    else {
      std::cerr << "read error" << std::endl;
      break;
    }
  }
  return 0;
}
