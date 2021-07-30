#include <stdio.h>
#define SUM_END 1000
#define FACT_COUNT 10
int fact (int input){
  if (input<=2){
    return 1;
  }

  return (fact(input-1)+fact(input-2));
}

int main(){

  *(int *)(0x10000004) = 0x34;
  int sum = 0;
  int i;
  int* addr = malloc(0x10);

  float testp = 10;
  int value = testp * 1.01;
  *(int *)(0x10000004) = 0x34;
  *(int *)(0x10000004) = 0x34;
  *(int *)(0x10000004) = 0x34;
  *(int *)(0x10000004) = 0x34;

  printf("hello\n\r");
  *(int *)(0x10000004) = 0x34;
  *(int *)(0x10000004) = 0x34;
  *(int *)(0x10000004) = 0x34;
  *(int *)(0x10000004) = 0x34;

  for(i = 0;i<SUM_END+1;i++)
  {
    sum += i;
    *addr = sum;
    *(((int*)0x90000000)+i) = sum;
    *(((int*)0x88000000)+i) = *(((int*)0x90000000)+i);
  }
  return 0;
}