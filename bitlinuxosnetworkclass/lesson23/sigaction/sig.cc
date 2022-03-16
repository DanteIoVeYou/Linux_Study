#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

int flag = 0;
void handler(int signo) {
  flag = 1;
  int cnt = 5;
  while(cnt) {
    cout << "cnt: " << cnt << endl;
    sleep(1);
    cnt--;
  }
  cout << "flag == 1, proc end by " << signo << endl;
}
int main() {
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, 3);
  struct sigaction action;
  struct sigaction oldaction;
  action.sa_handler = handler;
  action.sa_mask = set;
  action.sa_flags = 0;
  sigaction(SIGINT, &action, &oldaction);
  while(!flag) {
    ;
  }
  return 0;
}
