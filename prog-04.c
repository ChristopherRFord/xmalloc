#include "xmalloc.h"

/**
 * prog-04.c
 * This program tests xfree on an illegal memory address.
 * It should warn the programmer and exit.
 */
int main()
{
  xfree(0);

  if (bytesAllocated() > 0)
  {
      printf("There is a memory leak somewhere in this program\n");
      return 1;
  }

  return 0;
}
