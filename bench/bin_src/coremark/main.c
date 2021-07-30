#include <stdio.h>
#include "core_portme.h"
#define SUM_END 1000
#define FACT_COUNT 10
int fact (int input){
  if (input<=2){
    return 1;
  }

  return (fact(input-1)+fact(input-2));
}

int main(){
  int sum = 0;
  int i;
  int* addr = malloc(0x10);
  printf("hello\n\r");

  start_time();
  stop_time();

  printf("%d\n\r",get_time());

  return 0;
}