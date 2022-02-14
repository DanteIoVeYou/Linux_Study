#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
  printf("I am a process, pid: %d, ppid: %d\n", getpid(), getppid()); 
  printf("%s\n",getenv("MY_VAL"));
  printf("%s\n",getenv("PATH"));
  printf("%s\n",getenv("SHELL"));
  printf("%s\n",getenv("HOME"));
  printf("%s\n",getenv("HISTSIZE"));
  return 0;
}
