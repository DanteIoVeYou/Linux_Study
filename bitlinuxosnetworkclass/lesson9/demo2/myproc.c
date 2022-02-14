#include <stdio.h>
#include <unistd.h>
int main() {
  printf("I am father: %d\n", getpid());
  pid_t ret = fork();
  if(ret == 0) {
    while(1) {
      printf("I am a process, pid: %d, ppid: %d\n",getpid(), getppid());
      sleep(1);
    }
  }
  else if(ret > 0) {
    while(1) {
      printf("I am a process, pid: %d, ppid: %d\n",getpid(), getppid());
      sleep(1);
    }
  }
  else {

  }
  return 0;
}
