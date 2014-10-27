#include "xmalloc.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * xmalloc.c
 * Contains the void* xmalloc(int nBytes) and void xfree(void* ptr)
 * functions that check for double frees, non-existing mallocs,
 * memory leaks and trying to free the pointer in the middle
 * of an allocated memory chunck. Utilizes a linked list to manage
 * memory chuncks
 */

// Struct that defines a node in the linked list
// Contains memory address and size of memory chunk
struct MemoryNode
{
  void* address;
  int nBytes;

  struct MemoryNode* next;
  struct MemoryNode* prev;
};

// global variables for the library
static struct MemoryNode* HEAD;
static int INDEX = 0;

/**
 * xmalloc
 * Adds a MemoryNode (which represents a memory chunk) to the
 * global linked-list. Returns the address malloc'd 
 */
void* xmalloc(int nBytes)
{
  // CREATE A NEW HEAD BECAUSE THE LIST IS EMPTY
  if (INDEX == 0)
  {
    HEAD = (struct MemoryNode*) malloc(sizeof(struct MemoryNode));
    HEAD->next = NULL;
    HEAD->prev = NULL;
    HEAD->address = malloc(nBytes);
    HEAD->nBytes = nBytes;
    INDEX++;

    return HEAD->address; 
  }

  // CREATE A NEW NODE
  struct MemoryNode* newNode = (struct MemoryNode*) malloc(sizeof(struct MemoryNode));
  newNode->next = NULL;
  newNode->prev = NULL;
  newNode->address = malloc(nBytes);
  newNode->nBytes = nBytes;

  // ADD IT TO THE END OF THE LIST
  struct MemoryNode* next = HEAD;
  while (next->next != NULL) next = next->next;
  next->next = newNode;
  newNode->prev = next;
  INDEX++;

  return newNode->address;
}

/**
 * xfree
 * Attemps to free a memory address and remove the
 * memory chunk from the linked list. This function
 * will fail and exit the program if the memory address
 * passed over is not in the linked list, or if it is
 * in the middle of a memory chunk
 */
void xfree(void* memory)
{
  // CHECKING IF THE MEMORY ADDRESS IS LEGAL
  if (memory <= 0)
  {
    fprintf(stderr, "Illegal memory address\n");
    exit(1);
  }

  // CHECKING IF THE LINKED-LIST IS EMPTY
  if (INDEX == 0)
  {
    fprintf(stderr, "Either double free or memory was never malloc'd\n");
    exit(1);
  }

  // GOING THROUGH THE LINKED LIST UNTIL A NODE IS FOUND
  // OR MEMNODE IS NULL
  struct MemoryNode* memNode = HEAD;
  while (memNode != NULL)
  {
    // MEMORY ADDRESS WAS FOUND
    if (memNode->address == memory)
     break;
    // THE POINTER IS IN THE MIDDLE OF A MEMORY CHUNK
    else if (memory > memNode->address && memory <= memNode->address+memNode->nBytes)
    {
      printf("Memory address being freed is in the middle of a memory chunk\n");
      exit(1);
    }
    // POINTER IS NOT FOUND, CONTINUE LOOP
    else
      memNode = memNode->next;
  }

  // EITHER DOUBLE FREE OR THE MEMORY WAS NEVER MALLOC'D
  if (memNode == NULL)
  {
    fprintf(stderr, "Either double free or memory was never malloc'd\n");
    exit(1);
  }

  // MEMNODE IS THE HEAD
  if (memNode->prev == NULL)
  {
    HEAD = HEAD->next;
    if (HEAD != NULL)
      HEAD->prev = NULL;
  }
  // MEMNODE IS AT THE END OF THE LIST
  else if (memNode->next == NULL)
  {
    struct MemoryNode* prev = memNode->prev;
    prev->next = NULL;
  }
  // MEMNODE IS IN THE MIDDLE OF THE LIST
  else
  {
    struct MemoryNode* next = memNode->next;
    struct MemoryNode* prev = memNode->prev;

    prev->next = next;
    next->prev = prev;
  }

  // FREEING EVERYTHING UP
  INDEX--;
  free(memNode);
  free(memory);
}

/**
 * bytesAllocated
 * Returns the current amount of bytes xmalloc'd. This function
 * can be used to detect memory leaks at the end of the program
 */
int bytesAllocated()
{
  int bytesAllocated = 0;
  struct MemoryNode* memNode = HEAD;
  while(memNode != NULL)
  {
    bytesAllocated += memNode->nBytes;
    memNode = memNode->next;
  }

  return bytesAllocated;
}
