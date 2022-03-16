#include <iostream>
#include <pthread.h>
#include <unistd.h>
void* ThreadRoute(void* args) {
  int cnt = 0;
  while(cnt < 5) {
    std::cout << "args: " << (char*)args << std::endl;
    cnt++;
    sleep(1);
  }
  std::cout << "Thread exit" << std::endl;

  return nullptr;
}
int main()
{
  pthread_t tid; 
  int thread_id = pthread_create(&tid, nullptr, ThreadRoute, (void*)"I am thread");
  while(true) {
    std::cout << "I am main process" << std::endl;

    sleep(2);
  }
  return 0;
}
