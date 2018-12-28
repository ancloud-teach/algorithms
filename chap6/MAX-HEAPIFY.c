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

extern int istep;

void maxHeapify(int A[], int const length, int const heapsize, int i)
{
    int ileft = i << 1;
    int iright = (i << 1) + 1;
    int ilargest = i;

    int tmp;
    if (ileft<heapsize && A[ileft]>A[i]){
        ilargest = ileft;
    }

    if (iright<heapsize && A[iright] > A[ilargest]) {
        ilargest = iright;
    }

    //printf ("%s:%d ilarget=%d, i=%d\n", __FILE__, __LINE__, ilargest, i);

    if (ilargest != i) {
        istep++;

        tmp = A[i];
        A[i] = A[ilargest];
        A[ilargest] = tmp;
        maxHeapify(A, length, heapsize, ilargest);
    }
}