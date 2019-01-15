#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include "../init.h"
#include "./heap.h"


extern int istep;


/*
MIN-HEAPIFY(A, i)
    l = LEFT(i)
    r = RIGHT(i)
    if l <= A.heap-size and A[l] < A[i]
        smallest  = l
    if r <= A.heap-size and A[r] < A[smallest ]
        smallest  = r
    if smallest  != i
        exchange A[i] with A[smallest ]
        MIN-HEAPIFY(A, smallest )
 *
 * @i, is start at 0
 */
void minHeapify(AData A[], int const length, int const heapsize, int i)
{
    int ileft = LEFT(i);
    int iright = RIGHT(i);
    int ismallest = i;

    AData tmp;
    if (ileft<heapsize && A[ileft].value<A[i].value){
        ismallest = ileft;
    }

    if (iright<heapsize && A[iright].value < A[ismallest].value) {
        ismallest = iright;
    }

    if (ismallest != i) {
        //istep++;

        tmp = A[i];
        A[i] = A[ismallest];
        A[ismallest] = tmp;
        minHeapify(A, length, heapsize, ismallest);
    }
}

/*
BUILD-MIN-HEAPIFY(A)
    A.heap-size = A.length
    for i = [A.length/2] downto 1
        MIN-HEAPIFY(A, i)
*/
void buildMinHeapify(AData A[], int const length)
{
    int heapsize = length;

    for (int i=(length>>1); i >= 0; i--){
        //printf ("len=%d heapsize=%d, i=%d \n", length, heapsize, i);
        minHeapify(A, heapsize, length, i);
    }
}


/*
HEAP-MIN-SORT(A)
    BUILD-MAX-HEAPIFY(A)
    for i = A.length downto 2
        exchange A[1] with A[i]
        A.heapsize = A.heapsize - 1
        MAX-HEAPIFY(A, 1)
*/
void heapMinSort(AData A[], int length)
{
    AData tmp;
    int const size = length;

    buildMinHeapify(A, length);
    for (int i = length-1; i >= 1; i--) {
        tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;

        length--;
        minHeapify(A, length, length, 0); 
    }
}


/*
HEAP-MINIMUM(A)
    return A[1]
*/
AData heapMin(AData A[])
{
    return A[0];
}

/*
HEAP-EXTRACT-MIN(A)
    if A.heapsize < 1
        error "heap overflow"

    min = A[1]
    A[1] = A[A.heapsize]
    A.heapsize = A.heapsize - 1
    MIN-HEAPIFY(A, 1)
    return A[min]
 */
AData heapExtractMin(AData A[], int const len, int * heapsizep)
{
    assert(*heapsizep >= 1);
    
    AData min = A[0];
    A[0] = A[*heapsizep - 1];
    *heapsizep = *heapsizep - 1;
    minHeapify(A, len, *heapsizep, 0);
    
    return min;
}

/*
HEAP-DECREASE-KEY(A, i, key)
    if A[i] > key
        error "now key is larger than current key"
    A[i] = key
    while i > 1 and A[PARENT(i)] > A[i]
        exchange A[i] with A[PARENT(i)]
        i = PARENT(i)
*/
/* @i: the index, it is start at 0 */
void heapDecreaseKey(AData A[], int i, AData key)
{
    if (key.value > A[i].value)
        return;

    AData tmp;

    A[i] = key;
    if (i <= 0)
        return;
    int iparent = PARENT(i);

    while (i > 0 && A[iparent].value > A[i].value) {
        tmp = A[iparent];
        A[iparent] = A[i];
        A[i] = tmp;
        i = iparent;
        iparent = PARENT(i) ;
    }
}

/*
MIN-HEAP-INSERT(A, key)
    A.heapsize = A.heapsize + 1
    A[A.heapsize] = +8
    HEAP-DECREASE-KEY(A, A.heapsize, key)
*/
void minHeapInsert(AData A[], AData key, int *heapsizep)
{
    *heapsizep += 1;
    A[*heapsizep - 1].value = INT_MAX ;
		
    heapDecreaseKey(A, *heapsizep - 1, key);
}
