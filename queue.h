#ifndef __QUEUE_H_
#define __QUEUE_H_

#include <stdio.h>

typedef struct{
    void *elems;
    int elemSize;
    int start;
    int end;
    int allocLength;
} Queue;

void queueNew(Queue *q,int elemSize);
void queueDispose(Queue *q);
int isQueueEmpty(const Queue *q);
void enQueue(Queue *q, const void *elemAddr);
void deQueue(Queue *q, void *elemAddr);

#endif
