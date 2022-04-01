#include "BlockQueue.hpp"
void* consumer(void* args) {
  BlockQueue<int>* bq = (BlockQueue<int>*)args;
  while(true) {
    sleep(1);
    int out;
    bq->Get(&out);
    cout << "consumer: " << out << endl;
  }
}
void* productor(void* args) {
  srand((unsigned)time(nullptr));
  BlockQueue<int>* bq = (BlockQueue<int>*)args;
  while(true) {
    int in = rand() % 100;
    bq->Put(in);
    cout << "productor: " << in << endl;
  }
}
int main()
{
  BlockQueue<int>* bq = new BlockQueue<int>;
  pthread_t c;
  pthread_t p;
  pthread_create(&c, nullptr, consumer, (void*)bq);
  pthread_create(&p, nullptr, productor, (void*)bq);
  pthread_join(c, nullptr);
  pthread_join(p, nullptr);
  delete bq;
  return 0;
}
