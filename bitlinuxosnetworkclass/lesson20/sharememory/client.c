#include "common.h"
int main(){
  
  key_t key = ftok(PATH_NAME, PROJ_ID);
  if(key == -1) {
    perror("ftok");
    return 1;
  }

  int shmid = shmget(key, SIZE, IPC_CREAT);
  if(shmid == -1) {
    perror("shmget");
    return 2;
  }

  sleep(5);
  char* start = (char*)shmat(shmid, NULL, 0);
  if(start == (void*)-1) {
    perror("shmat");
    return 3;
  }
  sleep(5);


  char ch = 'A';
  while(ch<='Z') {
    start[ch-'A'] = ch;
    ch++;
    sleep(1);
  }

  shmdt(start);
  printf("%x\n", key);
  return 0;
} 
