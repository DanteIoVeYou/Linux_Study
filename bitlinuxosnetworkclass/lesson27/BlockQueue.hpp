#include <iostream>
#include <queue>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#define CAPACITY 10;
using namespace std;
template<class T>
class BlockQueue {
public:
  BlockQueue()
    :_cap(0)
  {
    pthread_mutex_init(&lock, nullptr);
    pthread_cond_init(&have_space, nullptr);
    pthread_cond_init(&have_data, nullptr);
  }
  
  ~BlockQueue()
  {
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&have_space);
    pthread_cond_destroy(&have_data);
  }

  bool IsEmpty() {
    return _cap == 0;
  }

  bool IsFull() {
    return _cap == CAPACITY;
  }

  void Put(const T& in) {
    pthread_mutex_lock(&lock);
    while(IsFull()) {
      pthread_cond_wait(&have_space, &lock);
    }
    _bq.push(in);
    _cap++;
    pthread_cond_signal(&have_data);
    pthread_mutex_unlock(&lock);
  }

  void Get(T* out) {
    pthread_mutex_lock(&lock);
    while(IsEmpty()) {
      pthread_cond_wait(&have_data, &lock);
    }
    *out = _bq.front();
    _bq.pop();
    _cap--;
    pthread_cond_signal(&have_space);
    pthread_mutex_unlock(&lock);
  }

private:
  int _cap;
  queue<T> _bq;
  pthread_mutex_t lock;
  pthread_cond_t have_space;
  pthread_cond_t have_data;
};

