#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define MAX_SIZE 256
int main() {
  char buffer[MAX_SIZE];
  char* prompt = "minishell@host #";
  while(1) {
  
    printf("%s", prompt);
    fgets(buffer, MAX_SIZE, stdin);
    char* p = strtok(buffer, " ");
    while(p) {
      if(p != NULL)
        printf("%s", p);
      p = strtok(NULL, " ");
    }
  }
  buffer[strlen(buffer) - 1] = 0;
  return 0;
}
