#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  printf("my proc begin\n");
  //execl("/usr/bin/ls", "ls", "-a", "-l", "-i", NULL);
  //execl("/usr/bin/touch", "touch", "111.txt", NULL);
  //execl("/usr/bin/echo", "echo",  "helloworld" ,">>" ,"111.txt", NULL);
  printf("my proc end\n");
  return 0;
}
