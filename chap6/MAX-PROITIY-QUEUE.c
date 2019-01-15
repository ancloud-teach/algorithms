#include <assert.h>
#include <limits.h>

#include "../init.h"

extern void maxHeapify(AData A[], int const length, int const heapsize, int i);
extern void buildMaxHeapify(AData A[], int const length);

/*
HEAP-MAXIMUM(A)
    return A[1]
*/
AData heapMax(AData A[])
{
    return A[0];
}

/*
HEAP-EXTRACT-MAX(A)
    if A.heapsize < 1
        error "heap overflow"

    max = A[1]
    A[1] = A[A.heapsize]
    A.heapsize = A.heapsize - 1
    MAX-HEAPIFY(A, 1)
    return max
 */
AData heapExtractMax(AData A[], int const len, int * heapsizep)
{
    assert(*heapsizep >= 1);
    
    AData maxp = A[0];
    A[0] = A[*heapsizep - 1];
    *heapsizep = *heapsizep - 1;
    maxHeapify(A, len, *heapsizep, 0);
    
    return maxp;
}

/*
HEAP-INCREASE-KEY(A, i, key)
    if A[i] < key
        error "now key is smaller than current key"
    A[i] = key
    while i > 1 and A[PARENT(i)] < A[i]
        exchange A[i] with A[PARENT(i)]
        i = PARENT(i)
*/
/* @i: the index, it is start at 0 */
void heapIncreaseKey(AData A[], int i, AData key)
{
    if (key.value < A[i].value)
        return;

    AData tmp;

    A[i] = key;
    if (i <= 0)
        return;
    int iparent = ((i+1) >> 1) - 1;

    while (i > 0 && A[iparent].value < A[i].value) {
        tmp = A[iparent];
        A[iparent] = A[i];
        A[i] = tmp;
        i = iparent;
        iparent = ((i+1) >> 1) - 1;
    }
}

/*
MAX-HEAP-INSERT(A, key)
    A.heapsize = A.heapsize + 1
    A[A.heapsize] = -8
    HEAP-INCREASE-KEY(A, A.heapsize, key)
*/
void maxHeapInsert(AData A[], AData key, int *heapsizep)
{
    *heapsizep += 1;
    A[*heapsizep - 1].value = INT_MIN;
    heapIncreaseKey(A, *heapsizep - 1, key);
}
