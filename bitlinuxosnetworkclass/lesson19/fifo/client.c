#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define PATH "./.fifo"
int main() {
  // wirte
  
  ssize_t fd = open(PATH, O_WRONLY, 0644);
  if(fd < 0) {
    perror("open");
    return 1;
  }
  
  char msg[128];
  while(1) {
    printf("client# ");
    fflush(stdout);
    msg[0] = 0;
    ssize_t size = read(0, msg, 127);
    msg[size] = 0;
    write(fd, msg, strlen(msg));
  }
  
  close(fd);
  return 0;
}
