#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void* thread_run(void* args) {
  while(1) {
    printf("%s\n", (char*)args);
    sleep(1);
  }
}
int main()
{

  pthread_t tid;
  int addrthread = pthread_create(&tid, NULL, thread_run,(void*)"hello");
  while(1) {

    printf("tid: %lu, main tid: %lu\n", tid, pthread_self());
    sleep(1);
  }
  return 0;
}
