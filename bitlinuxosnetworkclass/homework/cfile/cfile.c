#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
  
  
  FILE* fp = fopen("bite", "w");
  const char* buffer = "linux so easy\n";
  fwrite(buffer, 1, strlen(buffer), fp);
  fclose(fp);
  fp = fopen("bite", "r");
  char output[128] = {0};
  fread(output, 1, 128, fp);
  fprintf(stdout, "%s", output);
  fclose(fp);
  return 0;
}

