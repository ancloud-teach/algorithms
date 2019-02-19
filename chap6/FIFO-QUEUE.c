#include "./MIN-PROITIY-QUEUE.h"

int cnt = 0;
void fifoPush(AData queue[], AData data, int *sizep)
{
	data.value = cnt++;
	minHeapInsert(queue, data, sizep);
}

AData fifoPop(AData queue[], int const queueLen, int *sizep)
{
	return heapExtractMin(queue, queueLen, sizep);
}

