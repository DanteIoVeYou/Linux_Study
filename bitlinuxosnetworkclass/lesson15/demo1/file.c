#include <stdio.h>
#include <string.h>
int main() {
  fprintf(stdout, "hello\n");
  FILE* fp = fopen("test.txt","w");
  char* buffer[128];
  fread(buffer, 1, 10, stdin);
  if(fp == NULL) {
    perror("fopen");
    return 1;
  }
  const char* msg = "hello world\n";
  fwrite(buffer, 1, strlen(msg), stdout);
  fclose(fp);
  return 0;
}
