#include "../init.h"

extern AData heapExtractMax(AData A[], int const len, int * heapsizep);
extern void maxHeapInsert(AData A[], AData key, int *heapsizep);

int cnt = 0;
void lifoPush(AData queue[], AData data, int *sizep)
{
	data.value = cnt++;
	maxHeapInsert(queue, data, sizep);
}

AData lifoPop(AData queue[], int const queueLen, int *sizep)
{
	return heapExtractMax(queue, queueLen, sizep);
}

