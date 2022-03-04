#include "common.h"
int main() {

  key_t key = ftok(PATH_NAME, PROJ_ID);
  printf("key: %x\n", key);
}
