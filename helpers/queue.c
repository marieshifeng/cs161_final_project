/*
 * This is an array implementation of an integer stack.
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"   

queueT QueueInit(int maxSize){
  queueT queueP;
  queueP = malloc(sizeof(struct queue));
  int* newContents;
  newContents = malloc(sizeof(int) * maxSize);
  if (newContents == NULL){
    fprintf(stderr, "Insufficient memory to initalize queue.\n");
    exit(1);
  }
  queueP->contents = newContents;
  queueP->maxSize = maxSize;
  queueP->front = -1;
  queueP->rear = -1;
  return queueP; 
}

void QueueDestroy(queueT queueP){
  free(queueP->contents);
  queueP->contents = NULL;
  queueP->maxSize = 0;
  queueP->front = 0;
  queueP->rear = -1;
  free(queueP);
}

void QueueEnqueue(queueT queueP, int element){
  if (QueueIsFull(queueP)){
    fprintf(stderr, "Can't enqueue element: queue is full.\n");
    exit(1);
  }
  queueP->contents[queueP->rear++] = element;

}

int QueueDequeue(queueT queueP){
  if (QueueIsEmpty(queueP)) {
    fprintf(stderr, "Cannot dequeue: queue is already empty.\n");
    exit(1);
  }
  return queueP->contents[queueP->front++];
}

int QueueIsEmpty(queueT queueP){
  return (queueP -> rear < 0 || queueP -> rear == queueP -> front);
}

int QueueIsFull(queueT queueP){
  return queueP->rear >= queueP->maxSize -1;
}