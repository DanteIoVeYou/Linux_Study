#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <stdlib.h>
int main() {
  int pipe_fd[2] = {0};
  if(pipe(pipe_fd) < 0) {
    perror("pipe");
    return 1;
  }

  pid_t id = fork();
  if(id < 0) {
    perror("fork");
    return 2;
  }
  else if(id == 0) {
    // child
    // write
   
    
    close(pipe_fd[0]); // close read
    const char* msg = "helloworld";
    int cnt = 5;
    while(cnt--) {
      write(pipe_fd[1], msg, strlen(msg));
      sleep(1);
    }
    close(pipe_fd[1]);
    exit(1);
  }
  else {
    // father
    // read
    
    close(pipe_fd[1]); // close write
  

    while(1) {
      
      char buffer[128] = {0};
      ssize_t size = read(pipe_fd[0], buffer, 127);
      if(size > 0) {
        printf("father gets a msg from child: %s\n", buffer);
      }
      else if(size == 0) {
        printf("pipe closed\n");
        break;
      }
      else {
        //TODO
      }

    }

      close(pipe_fd[0]);


    int status = 0;
    if(waitpid(id, &status, 0) > 0) {
      printf("Wait success\n");
    }
    
  }
  printf("%d %d\n", pipe_fd[0], pipe_fd[1]);
  return 0;
}
