#include "ThreadPool.hpp"
#include "ThreadTask.hpp"
#include <string>
#include <unistd.h>
int main()
{
  srand((unsigned)time(NULL));
  std::string op = "+-*/%"; 
  ThreadPool<Task> tp;
  tp.ThreadPoolInit();
  while(true) {
    //std::cout << "starting load task..." << std::endl;
    int x = rand()%100+1;
    int y = rand()%100+1;
    tp.ThreadPoolPush(Task(op[rand()%5], x, y)); 
    sleep(1);
  }
  return 0;
}
