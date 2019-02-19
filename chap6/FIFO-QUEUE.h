#ifndef _FIFO_QUEUE_H_
#define _FIFO_QUEUE_H_
#include "../init.h"

/*
 * fifoPush
 *
 * @queue, the queue buffer
 * @key, the data would be push in
 * @sizep, the size of queue
 */
void fifoPush(AData queue[], AData data, int *sizep);

/*
 * fifoPop
 *
 * @queue, the queue buffer
 * @queueLen, the length of queue buffer
 * @sizep, the size of queue
 */
AData fifoPop(AData queue[], int const queueLen, int *sizep);

#endif

