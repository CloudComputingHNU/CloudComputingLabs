#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

#define RUN_TIMES 50000000

// #define DO_THING pthread_mutex_lock(&testMutex);pthread_mutex_unlock(&testMutex);
// #define DO_THING_2 DO_THING DO_THING
// #define DO_THING_4 DO_THING_2 DO_THING_2
// #define DO_THING_8 DO_THING_4 DO_THING_4
// #define DO_THING_16 DO_THING_8 DO_THING_8
// #define DO_THING_32 DO_THING_16 DO_THING_16
// #define DO_THING_64 DO_THING_32 DO_THING_32
// #define DO_THING_128 DO_THING_64 DO_THING_64

pthread_mutex_t testMutex=PTHREAD_MUTEX_INITIALIZER;

double time_diff(struct timeval x , struct timeval y, int currentTime)
{
  double x_ms , y_ms , diff;
  x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
  y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
  diff = (double)y_ms - (double)x_ms;
  if(diff<0)
  {
    fprintf(stderr, "ERROR! time_diff<0\n");
    exit(1);
  }
  printf("CurrentTime is %d\n",currentTime);
  return diff;
}

double CountAvgDelay(double totalTime, int runTimes)
{
  return totalTime/runTimes;
}

int main(int argc, char *argv[])
{
  struct timeval tvStart,tvEnd;
  int i=0;
  gettimeofday(&tvStart,NULL);
  for(i=0;i<RUN_TIMES;i++)
  {
    pthread_mutex_lock(&testMutex);
    pthread_mutex_unlock(&testMutex);
    // DO_THING_128
  }
  gettimeofday(&tvEnd,NULL);

  double totalTime=time_diff(tvStart,tvEnd);
  double avgDelay=totalTime/RUN_TIMES;

  printf("Total time %.3lf s, Average time per mutex lock() & unlock() is %.5lf us\n",totalTime/1E6,avgDelay);

  exit(0);
}
