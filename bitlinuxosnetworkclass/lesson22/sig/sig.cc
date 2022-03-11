#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  sigset_t in;
  sigset_t out;
  sigemptyset(&in);
  sigemptyset(&out);

  sigaddset(&in, SIGINT);
  sigprocmask(SIG_SETMASK, &in, &out);


  sigset_t pending;
  while(true) {
    sigpending(&pending);
    for(int i = 1; i < 32; i++) {
      if(sigismember(&pending, i)) {
        std::cout << 1;
      }
      else {
        std::cout << 0;
      }
    }
    std::cout << std::endl;
    sleep(1);
  }
  return 0;
}
