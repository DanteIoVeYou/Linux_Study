#include <stdio.h>
#include <unistd.h>
int main() {
  printf("I am a process\n");
  pid_t id = fork();
  if(id < 0) {
    perror("fork");
    return 1;
  }
  // child
  else if(id == 0) {
    while(1) {
      printf("I am child, ppid: %d, pid: %d\n", getppid(), getpid());
      sleep(1);
    }
  }
  //father
  else {
    while(1) {
      printf("I am father, ppid: %d, pid: %d\n", getppid(), getpid());
      sleep(1);
    }
  }
  return 0;
}
