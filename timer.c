// Hint: Don't name the execution file time.

#include <time.h>
#include <stdio.h>

int main(void)
{
  //
  // Initialization
  //
  printf("Initialization\n");
  clock_t start, diff;
  int msec, i;
 
  // 
  // Start timer
  //
  printf("Start Timer\n");
  start = clock();
  for (i = 0; i < 99999999; i++)
  {
  }// for
  
  //
  // Win
  //
  printf("About to WIN\n");
  diff = clock() - start;
  msec = diff * 1000 / CLOCKS_PER_SEC;
  printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
  
  return 0;
}
