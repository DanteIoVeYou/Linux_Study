#include <stdio.h>
#include <unistd.h>
int main() {

  printf("I am a zombie process demo\n");
  pid_t id = fork();
  if(id < 0) {
    perror("fork");
    return 1;
  }
  // child
  else if(id == 0) {
    int count = 5;
    while(count--) {
      printf("I am child, ppid: %d, pid: %d\n", getppid(), getpid());
      sleep(1);
    }
  }
  //father
  else {
    int count = 10;
    while(count--) {
      printf("I am father, ppid: %d, pid: %d\n", getppid(), getpid());
      sleep(1);
    }
  }
  return 0;
}
