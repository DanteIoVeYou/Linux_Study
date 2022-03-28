#include <iostream>
#include <pthread.h>
#include <unistd.h>
#define NUM 5

using namespace std;

int tickets = 1000;
void* routine(void* args) {
  while(true) {
    if(tickets > 0) {
      usleep(1000);
      printf("thread NO.  0x%x get a ticket, %d left\n",  pthread_self(), tickets--);
      usleep(1000);
    }
    else {
      printf("0x%x qiut... ticket: %d\n", pthread_self(), tickets);
      break;
    }
  }
  return nullptr;
}
int main()
{
  pthread_t tids[NUM];
  for(int i = 0; i < NUM; i++) {
    pthread_create(tids+i, nullptr, routine, nullptr);
  }
  for(int i = 0; i < NUM; i++) {
    pthread_join(tids[i], nullptr);
  }
  return 0;
}
