#include <stdio.h>
#include <unistd.h>
int main() {
  execlp("ls", "-a", "-l", NULL);
  return 0;
}
