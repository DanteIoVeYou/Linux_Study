#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define PATH "./.fifo"
int main() {
  int ret = mkfifo(PATH, 0644);
  if(ret < 0) {
    perror("mkfifo");
    return 1;
  }

  int fd = open(PATH, O_RDONLY, 0644);
  if(fd < 0) {
    perror("open");
    return 1;
  }
  while(1) {
    char buffer[128];
    buffer[0] = 0;
    ssize_t size = read(fd, buffer, sizeof(buffer) - 1);
    if(size < 0) {
      perror("read");
      return 3;
    }
    else if(size == 0) {
      printf("lient quit...\n");
      break;
    }
    else {
      buffer[size] = 0;
      printf("client$ %s", buffer);
      fflush(stdout);
    }
  }



  close(fd);
  return 0;
}
