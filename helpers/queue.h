/*  
 * This is the interface for a queue of integers.
 */

#ifndef _QUEUE_H
#define _QUEUE_H

struct queue{
  int* contents;
  int maxSize;
  int frontIndex;
  int rearIndex;
};

typedef struct queue* queueT;
queueT QueueInit(int maxSize);
void QueueDestroy(stackT stackP);
void QueueEnqueue(stackT stackP, int element);
int QueueDeQueue(stackT stackP);
int QueueIsEmpty(stackT stackP);

#endif  /* not defined _QUEUE_H */