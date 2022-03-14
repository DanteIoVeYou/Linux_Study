#include "common.h"
int main() {
  key_t key = ftok(PATH_NAME, PROJ_ID);
  if(key == -1) {
    perror("ftok");
    return 1;
  }

  printf("key: %x\n", key);

  int shmid = shmget(key, SIZE, IPC_CREAT|IPC_EXCL|0644);

  if(shmid == -1) {
    perror("shmget");
    return 2;
  }

  printf("shmid: %d\n", shmid);
  sleep(5);


  char* start = (char*)shmat(shmid, NULL, 0);
  if(start == (void*)-1) {
    perror("shmat");
    return 3;
  }
  printf("shmat success...\n");
  sleep(5);
  while(1) {
    printf("%s\n", start);
    sleep(1);
  }


  shmdt(start);
  sleep(5);
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
}
