#include <stdio.h>
#include <unistd.h>
int main() {
  pid_t id = fork();
  
  if(id == 0) {
    sleep(5);
    int a = 3/0;
  }
  else if(id > 0) {
    while(1) {
      printf("father: I am alive\n");
      sleep(1);
    }
  }
  return 0;
}
