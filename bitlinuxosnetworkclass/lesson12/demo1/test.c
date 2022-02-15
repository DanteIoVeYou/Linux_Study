#include <stdio.h>
#include <unistd.h>
//int main() {
//  char* str = "hello world";
//  fork();
//  while(1) {
//    printf("pid: %d, str: %s\n", getpid(), str);
//    sleep(1);
//  }
//  return 0;
//} 
int main() {
  pid_t id = fork();
  if(id == 0) {
    //child
    while(1) {
      printf("I am child\n");
      sleep(1);
    }
  }
  else if(id > 0) {
    //father
    while(1) {
      printf("I am father\n");
      sleep(1);
    }
  }
  else {
    perror("fork");
  }
  return 0;
}
