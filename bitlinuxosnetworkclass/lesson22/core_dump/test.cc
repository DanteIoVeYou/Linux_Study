#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
using namespace std;
int main() {
  pid_t id  = fork();
  if(id == 0) {
    //child
    int cnt = 5;
    while(cnt--) {
      cout << "I am child" << getpid() <<"count: " << cnt << endl;
      sleep(1);
    }
    //int a = 10;
    //int b = 0;
    //a = a/b;
    
    int* p;
    *p = 100;
    exit(0);
  }
  int status = 0;
  pid_t ret = waitpid(id, &status, 0);
  if(ret == id) {

    cout << "Succeed" << endl;
    cout << "exit code: " << ((status>>8)&0xff) << endl;
    cout << "sig: " << ((status)&0x7f) << endl;
    cout << "core dump: " << ((status>>7)&0x1) << endl;
  }
  return 0;
}
