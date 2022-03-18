#include <iostream>
#include <pthread.h>
#include <unistd.h>

#define NUMS 5
void* thread_run(void* args) {
  int cnt = 10;
  while(cnt) {
    std::cout << "thread: " << pthread_self() << std::endl;
    sleep(1);
    cnt--;
  }
  pthread_cancel(pthread_self());
  usleep(1);
  return (void*)18;
}
int main()
{

  pthread_t tids[NUMS];
  for(int i  = 0; i < NUMS; i++)
    pthread_create(tids+i, NULL, thread_run, (void*)"thread");
  sleep(1);
  //pthread_cancel(tids[4]);
  //pthread_cancel(tids[3]);
  for(int i = 0; i < NUMS; i++) {

    std::cout << " tid[" << i << "] is " << tids[i] << std::endl; 
    void* ret;
    pthread_join(tids[i], &ret);
    sleep(3);
    std::cout << "tid[" << i << "] end" << "exit code: " << (long long)ret<< std::endl;
  }
  sleep(1);
  return 0;
}
