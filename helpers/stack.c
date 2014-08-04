/*
 * This is an array implementation of an integer stack.
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"       

stackT StackInit(int maxSize) {
  stackT stackP;
  stackP = malloc(sizeof(struct stack));
  int *newContents;
  newContents = malloc(sizeof(int) * maxSize);
  if (newContents == NULL) {
    fprintf(stderr, "Insufficient memory to initialize stack.\n");
    exit(1);  /* Exit, returning error code. */
  }
  stackP->contents = newContents;
  stackP->maxSize = maxSize;
  stackP->top = -1;  /* Empty */
  return stackP;
}

void StackDestroy(stackT stackP) {
  free(stackP->contents);
  stackP->contents = NULL;
  stackP->maxSize = 0;
  stackP->top = -1;
  free(stackP);
}

void StackPush(stackT stackP, int element) {
  if (StackIsFull(stackP)) {
    fprintf(stderr, "Can't push element on stack: stack is full.\n");
    exit(1);  /* Exit, returning error code. */
  }
  stackP->contents[++stackP->top] = element;
}

int StackPop(stackT stackP) {
  if (StackIsEmpty(stackP)) {
    fprintf(stderr, "Can't pop element from stack: stack is empty.\n");
    exit(1);  /* Exit, returning error code. */
  }
  return stackP->contents[stackP->top--];
}

int StackPeek(stackT stackP) {
  if (StackIsEmpty(stackP)) {
    fprintf(stderr, "Can't pop element from stack: stack is empty.\n");
    exit(1);  /* Exit, returning error code. */
  }
  return stackP->contents[stackP->top];
}

int StackIsEmpty(stackT stackP) {
  return stackP->top < 0;
}

int StackIsFull(stackT stackP) {
  return stackP->top >= stackP->maxSize - 1;
}

int StackContains(stackT stackP, int element) {
  for (int i = 0; i < stackP->top; ++i) {
    if (stackP->contents[i] == element) { return 1; }
  }
  return 0;
}