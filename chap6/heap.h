#ifndef _HEAP_H_
#define _HEAP_H_

/*
 * the i is start at 0
 */
#define LEFT(i)         (((i+1)<<1)-1)
#define RIGHT(i)        ((((i+1)<<1)+1)-1)
#define PARENT(i)       (((i+1)>>1)-1)

#endif
