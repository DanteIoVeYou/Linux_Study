#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
  close(1);
  int fd = open("file.txt", O_WRONLY|O_CREAT, 0644);

  printf("helloworld\n");
  fflush(stdout);
  close(fd);
  return 0;
}
