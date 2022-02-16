#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  pid_t id = fork();
  if(id == 0) {
    //child proc
    int count = 5;
    while(count) {
     printf("child is running: %d, ppid: %d, pid: %d\n", count--, getppid(), getpid());
     sleep(1);
    }
    printf("child quit...\n");
  }
  else {
    //father proc
    printf("fatehr is waiting...\n");
    sleep(10);
    pid_t ret = wait(NULL);
    printf("child quit, father get its pid: %d\n", ret);
  }
  return 0;
}
