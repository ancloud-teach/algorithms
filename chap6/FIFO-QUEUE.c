#include "./MIN-PROITIY-QUEUE.h"

void fifoPush(AData queue[], AData data, int *sizep)
{
	data.value = *sizep;
	minHeapInsert(queue, data, sizep);
}

AData fifoPop(AData queue[], int const queueLen, int *sizep)
{
	return heapExtractMin(queue, queueLen, sizep);
}

