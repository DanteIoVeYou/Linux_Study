#include <stdio.h>
#include <unistd.h>
int main() {


  printf("I am father, my pid is %d\n", getpid());
  fork();




  while(1) {
    printf("I am process, my pid is %d, ppid is %d\n", getpid(), getppid());
    sleep(1);
  }
  return 0;

}
