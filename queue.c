#include "common.h"
#include "queue.h"

void queueNew(Queue *q,int elemSize)
{
    assert(elemSize > 0);
    q->elemSize = elemSize;
    q->start = -1;
    q->end = 0;
    q->allocLength = 40;
    q->elems = malloc(4 * elemSize);
    assert(q->elems != NULL);
}
void queueDispose(Queue *q)
{
    free(q->elems);
}
int isQueueEmpty(const Queue *q)
{
    return (q->start == -1 || q->start==q->end)?1:0;
}
void enQueue(Queue *q, const void *elemAddr)
{
    void *destAddr;
    if(q->end == q->allocLength){
        q->allocLength *= 2;
        q->elems = realloc(q->elems, q->allocLength * q->elemSize);
        assert(q->elems != NULL);
    }
    destAddr = (char *)q->elems + q->end * q->elemSize;
    memcpy(destAddr, elemAddr, q->elemSize);
    q->end++;
    if(q->start==-1) q->start=0;
}
void deQueue(Queue *q, void *elemAddr)
{
    const void *sourceAddr;
    assert(!isQueueEmpty(q));
    sourceAddr = (const char *)q->elems + q->start * q->elemSize;
    memcpy(elemAddr, sourceAddr, q->elemSize);
    q->start++;

    //When their is large free space in beginning of Queue
    if(q->start > q->allocLength/2){
        void *sAddr, *dAddr;
        for(int i=q->start; i<q->end; i++){
            dAddr = (char *)q->elems + (i-q->allocLength/2)* q->elemSize;
            sAddr = (char *)q->elems + i * q->elemSize;
            memcpy(dAddr, sAddr, q->elemSize);
        }
        q->start=q->start-q->allocLength/2;
        q->end=q->end-q->allocLength/2;
    }
}
