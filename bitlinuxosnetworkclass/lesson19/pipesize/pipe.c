#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>
int main()
{
  int pipefd[2] = {0};
  int ret = pipe(pipefd);
  if(ret < 0) {
    perror("pipe");
    return 1;
  }
  printf("pipefd[0]: %d pipefd[1]: %d\n", pipefd[0], pipefd[1]);
  
  pid_t id = fork();
  if(id < 0) {
    perror("fork");
    return 2;
  }
  else if(id == 0) {
    // child to write
    close(pipefd[0]); // 关闭子进程读端
    const char* msg = "a"; //让写端一次写一个字节，那么写了多少次就是多少字节
    int cnt = 0;
    while(1) {
      write(pipefd[1], msg, strlen(msg));
      cnt++;
      printf("write: %d\n", cnt);
    }
    close(pipefd[1]);
    exit(0);
  }

  
  // father to read 
  close(pipefd[1]);
  char buffer[64];
  buffer[0] = 0;
  while(1) {
    sleep(100);
    ssize_t size = read(pipefd[0], buffer, sizeof(buffer) - 1);
    if(size < 0) {
      perror("read");
      return 3;
    }
    else if(size == 0) {
      break;
    }
    buffer[size] = 0;
    printf("father get: %s", buffer);
  }
  close(pipefd[0]);
  int status = 0;
  pid_t waitret = waitpid(id, &status, 0);
  printf("wait succeed! exit code: %d.\n", (status>>8)&0xff);
  return 0;
}
