#include <iostream>
#include <unistd.h>

using namespace std;
int main() {

  alarm(1); // 一秒之后，会给目标进程发送SIGALRM
  int cnt = 0;
  while(1) {
    //cout << cnt++ << endl;
    cnt++;
  }

  cout <<"cnt: " <<cnt << endl;
  return 0;
}
