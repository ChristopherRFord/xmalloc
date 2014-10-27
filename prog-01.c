#include "xmalloc.h"
#include <stdio.h>

/**
 * prog-01.c
 * Tests xmalloc and xfree by allocating 4 pointers
 * of each size and freeing them. This program should
 * work.
 */
int main()
{
  int* ptr1 = xmalloc(sizeof(int));
  int* ptr2 = xmalloc(sizeof(int)*2);
  int* ptr3 = xmalloc(sizeof(int)*3);
  int* ptr4 = xmalloc(sizeof(int)*4);

  printf("Total bytes allocated: %i\n", bytesAllocated());

  xfree(ptr2);
  printf("After xfree ptr2: %i\n", bytesAllocated());

  xfree(ptr4);
  printf("After xfree ptr4: %i\n", bytesAllocated());

  xfree(ptr1);
  printf("After xfree ptr1: %i\n", bytesAllocated());

  xfree(ptr3);
  printf("After xfree ptr3: %i\n", bytesAllocated());


  if (bytesAllocated() > 0)
  {
    printf("There is a memory leak somewhere in this program\n");
    return 1;
  }
  return 0;
}
