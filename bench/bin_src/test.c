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
  int sum = 0;
  int i;
  for(i = 0;i<SUM_END+1;i++)
    sum += i;
    

  printf("Hello Me!\n");
  printf("sum 0 to %d = %d\n",SUM_END,sum);
  printf("Factorial %d = %d\n",FACT_COUNT,fact(FACT_COUNT));
  return 0;
}