/*  
 * This is the interface for a queue of integers.
 */

#ifndef _QUEUE_H
#define _QUEUE_H

struct queue{
  int* contents;
  int maxSize;
  int front;
  int rear;
};

typedef struct queue* queueT;
queueT QueueInit(int maxSize);
void QueueDestroy(queueT queueP);
void QueueEnqueue(queueT queueP, int element);
int QueueDequeue(queueT queueP);
int QueueIsEmpty(queueT queueP);
int QueueIsFull(queueT queueP);

#endif  /* not defined _QUEUE_H */