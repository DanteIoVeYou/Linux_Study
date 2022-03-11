#include <iostream>
#include <signal.h>
#include <sys/types.h>
using namespace std;
void Usage() {
  cout << "Usage:\n\t" << "./kill [SIG] [PID]" << endl;
  exit(1);
}
int main(int argc, char* argv[]) {


  if(argc != 3) {
    Usage();
  }
  else {
    kill(atoi(argv[2]), atoi(argv[1]));
  }
  return 0;
}
