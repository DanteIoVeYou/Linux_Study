#include <iostream>
#include <pthread.h>
#include <queue>
#include <mutex>

template<class T>
class ThreadPool {
public:
  ThreadPool(size_t threadNum = 5):_threadNum(threadNum) 
  {
    pthread_mutex_init(&_lock, nullptr);
    pthread_cond_init(&_cond, nullptr);
  }

  ~ThreadPool()
  {
    pthread_mutex_destroy(&_lock);
    pthread_cond_destroy(&_cond);
  }

  static void* Routinue(void* args) {
    // 首先分离线程
    pthread_detach(pthread_self());
    ThreadPool<T>* tp = (ThreadPool<T>*)args;
    while(true) {
      pthread_mutex_lock(&tp->_lock);
      while(tp->_queue.empty()) {
         pthread_cond_wait(&tp->_cond, &tp->_lock);
      }
      T task = tp->_queue.front();
      tp->_queue.pop();
      pthread_mutex_unlock(&(tp->_lock));
      std::cout << "[" << pthread_self() << "] ";
      task.run();
    }
  }
  
  void ThreadPoolInit()
  {
    // 创建_threadNum个线程，然后进行任务的分配
      for(size_t i = 0; i < _threadNum; i++) {
        pthread_t tid;
        pthread_create(&tid, nullptr, Routinue, this);
      }
  }

  void ThreadPoolPush(const T& task)
  {
    pthread_mutex_lock(&_lock);
    _queue.push(task);
    pthread_cond_signal(&_cond);
    pthread_mutex_unlock(&_lock);
  }

private:
  std::queue<T> _queue;
  pthread_mutex_t _lock;
  size_t _threadNum;
  pthread_cond_t _cond;
};
