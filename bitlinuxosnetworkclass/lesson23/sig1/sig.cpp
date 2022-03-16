#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

volatile int flag = 0;
void handler(int signo) {
  flag = 1;
//  cout << "sleep 3s" << endl;
//  sleep(3);
  cout << "flag == 1, proc end by " << signo << endl;
}
int main() {
  signal(SIGINT, handler);
  while(!flag) {
    ;
  }
  return 0;
}
