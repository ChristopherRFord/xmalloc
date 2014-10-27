#include "xmalloc.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * prog-05.c
 * This program causes a memory leak. It should
 * warn the programmer and exit accordinly.
 */
int main()
{
  int* ptr = xmalloc(sizeof(int) * 2);
  int* ptr1 = xmalloc(sizeof(int) * 3);

  xfree(ptr);

  if (bytesAllocated() > 0)
  {
      printf("There is a memory leak somewhere in this program\n");
      return 1;
  }

  return 0;
}
