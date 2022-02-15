#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int g_unval;
int g_val = 100;
int main(int argc, char* argv[], char* env[]) {
  printf("code addr:    %p\n", main); 
  char* str = "helloworld";
  printf("char addr:    %p\n", str);
  printf("val  addr:    %p\n", &g_val);
  printf("unvaladdr:    %p\n", &g_unval);
  int* p1 = (int*)malloc(10);
  int* p2 = (int*)malloc(10);
  int* p3 = (int*)malloc(10);
  int* p4 = (int*)malloc(10);
  printf("heap1 addr:   %p\n", p1);
  printf("heap2 addr:   %p\n", p2);
  printf("heap3 addr:   %p\n", p3);
  printf("heap4 addr:   %p\n", p4);
  int a1 = 10;
  int a2 = 10;
  int a3 = 10;
  int a4 = 10;
  printf("stack1 addr:    %p\n", &a1);
  printf("stack2 addr:    %p\n", &a2);
  printf("stack3 addr:    %p\n", &a3);
  printf("stack4 addr:    %p\n", &a4);


  printf("command pa addr:    %p\n", argv[0]);
  printf("command pa addr:    %p\n", argv[argc - 1]);

  printf("env addr:   %p\n", env[0]);
  return 0;
}
