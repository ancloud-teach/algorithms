#ifndef _MIN_PORITIY_QUEUE_H_
#define _MIN_PORITIY_QUEUE_H_
#include "../init.h"

void heapMinSort(AData A[], int length);
void heapDelete(AData A[], int i, int length, int * heapsizep);
AData heapMin(AData A[]);
AData heapExtractMin(AData A[], int const len, int * heapsizep);
void heapDecreaseKey(AData A[], int i, AData key);
void minHeapInsert(AData A[], AData key, int *heapsizep);

#endif
