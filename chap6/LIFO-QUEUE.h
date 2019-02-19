#ifndef _LIFO_QUEUE_H_
#define _LIFO_QUEUE_H_
#include "../init.h"

/*
 * lifoPush
 *
 * @queue, the queue buffer
 * @key, the data would be push in
 * @sizep, the size of queue
 */
void lifoPush(AData queue[], AData data, int *sizep);

/*
 * fifoPop
 *
 * @queue, the queue buffer
 * @queueLen, the length of queue buffer
 * @sizep, the size of queue
 */
AData lifoPop(AData queue[], int const queueLen, int *sizep);

#endif

