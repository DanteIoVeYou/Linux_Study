#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;
int main() {
  signal(SIGCHLD, SIG_IGN);
  if(fork() == 0) {
    // child
    int cnt = 5;
    while(cnt) {
      cout << "child: " << getpid() << " cnt: " << cnt << endl;
      cnt--;
      sleep(1);
    }
    exit(0);
  }
  //parent
  int cnt = 10;
  while(cnt) {
    cout << "parent: " << getpid() << " cnt: " << cnt << endl;
    cnt--;
    sleep(1);
  }
  
  return 0;
}

