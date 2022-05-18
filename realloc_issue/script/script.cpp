#include <stdio.h>
#include <stdlib.h>

extern "C" {

void test()
{
  void* holder = malloc(3145);
  printf("holder=%p\n", holder);
  void* buf = NULL;
  printf("buf=%p \n", buf);
  buf = realloc(buf, 1256);
  printf("buf=%p \n", buf);
}
}
