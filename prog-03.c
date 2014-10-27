#include "xmalloc.h"

/**
 * prog-03.c
 * This program tests for a double free using xfree.
 * It should notify the programemr that there is a dobule
 * free and exit accordinly.
 */
int main()
{
  int* ptr = xmalloc(sizeof(int) * 2);

  xfree(ptr);
  xfree(ptr);

  if (bytesAllocated() > 0)
  {
      printf("There is a memory leak somewhere in this program\n");
      return 1;
  }

  return 0;
}
