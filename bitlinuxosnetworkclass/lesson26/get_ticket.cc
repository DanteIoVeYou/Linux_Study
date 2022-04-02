#include <iostream>
#include <pthread.h>
#include <unistd.h>
#define NUM 5

using namespace std;

int tickets = 1000;
pthread_mutex_t lock;
struct arg{
  int x;
};
void* routine(void* args) {
  while(true) {
    pthread_mutex_lock(&lock);
    if(tickets > 0) {
      usleep(1000);
      printf("thread NO. %d 0x%x get a ticket, %d left\n", ((arg*)args)->x, pthread_self(), tickets--);
      usleep(1000);
      pthread_mutex_unlock(&lock);
    }
    else {
      printf("0x%x qiut... ticket: %d\n", pthread_self(), tickets);
      pthread_mutex_unlock(&lock);
      break;
    }
  }
  return nullptr;
}
int main()
{

  pthread_mutex_init(&lock, nullptr);
  arg* arg1 = new arg;
  arg1->x = 1;
  pthread_t tids[NUM];
  for(int i = 0; i < NUM; i++) {
    pthread_create(tids+i, nullptr, routine, arg1);
  }
  for(int i = 0; i < NUM; i++) {
    pthread_join(tids[i], nullptr);
  }
  pthread_mutex_destroy(&lock);
  return 0;
}
