/* random.c */
#include <stdlib.h>
#include <time.h>

int flag = 1;

int randomnum(int num){
  /*
  if(flag){
    srand((unsigned int)time(NULL));
    flag = 0;
  }
  */
  return rand()%num;
}
