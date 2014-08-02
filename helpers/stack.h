/*  
 * This is the interface for a stack of integers.
 */

#ifndef _STACK_H
#define _STACK_H

struct stack{
  int *contents;
  int maxSize;
  int top;
};

typedef struct stack *stackT;
stackT StackInit(int maxSize);
void StackDestroy(stackT stackP);
void StackPush(stackT stackP, int element);
int StackPop(stackT stackP);
int StackPeek(stackT stackP);
int StackIsEmpty(stackT stackP);
int StackIsFull(stackT stackP);
int StackContains(stackT stackP, int element);

#endif  /* not defined _STACK_H */