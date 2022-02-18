#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main() {
  close(1);
  int fd = open("log.txt", O_WRONLY|O_CREAT, 0644);
  char* buffer = "helloworld";
  //write(fd, buffer, strlen(buffer));
  printf("helloworld!\n");
  fflush(stdout);
  close(fd);
  return 0;
}
