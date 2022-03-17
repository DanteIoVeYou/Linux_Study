#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int ticket_cnt = 1000;
pthread_mutex_t lock;
void* thread_run(void* args) {
  while(1) {
    usleep(1000);
    pthread_mutex_lock(&lock);
    usleep(1000);
    if(ticket_cnt > 0) {
      usleep(70000);
      ticket_cnt--;
      printf("no %d get a ticket, left ticket: %d\n", (int)args, ticket_cnt);
      pthread_mutex_unlock(&lock);
    }
    else {
      pthread_mutex_unlock(&lock);
      break;
    }
  }
  return (void*)10;
}
int main()
{
  pthread_t tid1;
  pthread_t tid2;
  pthread_t tid3;
  pthread_t tid4;
  pthread_create(&tid1, NULL, thread_run, (void*)1);
  pthread_create(&tid2, NULL, thread_run, (void*)2);
  pthread_create(&tid3, NULL, thread_run, (void*)3);
  pthread_create(&tid4, NULL, thread_run, (void*)4);


  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  pthread_join(tid4, NULL);

  pthread_mutex_destroy(&lock);
  return 0;
}
