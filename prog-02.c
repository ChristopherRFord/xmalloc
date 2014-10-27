#include "xmalloc.h"

/**
 * prog-02.c
 * This program tests xfree in the middle of the
 * of a memory chunk. It should notify the programmer
 * that there is an error an exit accordingly.
 */
int main()
{
  int* ptr = xmalloc(sizeof(int)*4);
  ptr+= 1;

  xfree(ptr);

  if (bytesAllocated() > 0)
  {
      printf("There is a memory leak somewhere in this program\n");
      return 1;
  }
  return 0;
}
