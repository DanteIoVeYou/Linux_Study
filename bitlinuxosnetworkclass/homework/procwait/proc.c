#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
  pid_t id = fork();
  if(id < 0) {
    perror("fork");
    exit(1);
  }
  else if(id == 0) {
    // child
    int count = 20;
    while(count--) {
      printf("I am child process\n");
      sleep(1);
    }
    exit(10);
  }
  else {
    // father
    int status = 0;
    pid_t ret = waitpid(-1, &status, 0);
    if(ret > 0 && (status&0x7f) == 0) {
      printf("exit code: %d\n", (status>>8)&0xff);
    }
    else if(ret > 0) {
      printf("sig code: %d\n", (status)&0x7f);
    }
  }
  return 0;
} 
