#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void handler(int signo) {
  std::cout << " helloworld: " << signo << std::endl;
}
int main() {
  // sighandler_t sig = signal(SIGINT, handler);
  for(int i = 1; i < 32; i++) {
    signal(i, handler);
  }
  while(true) {
    std::cout << "I am a process: " << getpid() << std::endl;
    sleep(1);
  }
  return 0;
}
