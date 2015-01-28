#include <time.h>

int main(void)
{
  //
  // Initialization
  //
  clock_t start, diff;
  int msec, i;
 
  // 
  // Start timer
  //
  start = clock();
  for (i = 0; i < 9999999999; i++)
  {
  }// for
  
  //
  // Win
  //
  diff = clock() - start;
  msec = diff * 1000 / CLOCKS_PER_SEC;
  printf("Time taken %d seconds %d milliseconds", msec/1000, msec%1000);
  
  return 0;
}
