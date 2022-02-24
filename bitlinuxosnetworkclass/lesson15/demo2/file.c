#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main() {
//  int fd = open("test.txt", O_WRONLY|O_CREAT, 0644);
//  if(fd < 0) {
//    perror("open");
//    return 1;
//  }
//  const char* msg = "hello world\n";
//  write(fd, msg, strlen(msg));
//  printf("fd: %d\n",fd);
//
  int fd = open("test.txt", O_RDONLY, 0644);
  char buffer[1024];
  ssize_t ret = read(fd, buffer, 1023);
  if(ret > 0) {
    
    buffer[ret] = '\0';
    printf("%s\n", buffer);
  }
  close(fd);
  return 0;
}
