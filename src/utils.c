#include <stdio.h>
#include <sys/time.h>

#include "../include/linearSystem.h"

void printTime(struct timeval start, struct timeval end) {
  long seconds, useconds;
  seconds = end.tv_sec - start.tv_sec;
  useconds = end.tv_usec - start.tv_usec;

  long mtime = ((seconds * 1000) + useconds);

  printf("Tempo: %ld milisegundos\n", mtime);
}
