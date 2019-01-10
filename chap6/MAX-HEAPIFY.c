/*
MAX-HEAPIFY(A, i)
    l = LEFT(i)
    r = RIGHT(i)
    if l <= A.heap-size and A[l] > A[i]
        largest = l
    if r <= A.heap-size and A[r] > A[largest]
        largest = r
    if largest != i
        exchange A[i] with A[largest]
        MAX-HEAPIFY(A, largest)
*/
#include <stdio.h>
#include "../init.h"
#include "./heap.h"

extern int istep;

/*
 * @i, is start at 0
 */
void maxHeapify(AData A[], int const length, int const heapsize, int i)
{
    /*
    int ileft = i << 1;
    int iright = (i << 1) + 1;
    */
    int ileft = LEFT(i);
    int iright = RIGHT(i);
    int ilargest = i;

    AData tmp;
    if (ileft<heapsize && A[ileft].value>A[i].value){
        ilargest = ileft;
    }

    if (iright<heapsize && A[iright].value > A[ilargest].value) {
        ilargest = iright;
    }

    //printf ("%s:%d ilarget=%d, i=%d\n", __FILE__, __LINE__, ilargest, i);

    if (ilargest != i) {
        //istep++;

        tmp = A[i];
        A[i] = A[ilargest];
        A[ilargest] = tmp;
        maxHeapify(A, length, heapsize, ilargest);
    }
}