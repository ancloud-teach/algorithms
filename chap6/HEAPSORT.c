/*
HEAPSORT(A)
    BUILD-MAX-HEAPIFY(A)
    for i = A.length downto 2
        exchange A[1] with A[i]
        A.heapsize = A.heapsize - 1
        MAX-HEAPIFY(A, 1)
*/
#include <stdio.h>

extern void maxHeapify(int A[], int const length, int const heapsize, int i);
extern void buildMaxHeapify(int A[], int const length);

void heapSort(int A[], int length)
{
    int tmp;
    int const size = length;

    buildMaxHeapify(A, length);
    for (int i = length-1; i >= 1; i--) {
        tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;

        length--;
        maxHeapify(A, length, length, 0); 
    }
}