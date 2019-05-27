/*
BUILD-MAX-HEAPIFY(A)
    A.heap-size = A.length
    for i = [A.length/2] downto 1
        MAX-HEAPIFY(A, i)
*/
#include <stdio.h>

extern void maxHeapify(int A[], int const length, int const heapsize, int i);
void buildMaxHeapify(int A[], int const length)
{
    int heapsize = length;

    for (int i=(length>>1); i >= 0; i--){
        //printf ("len=%d heapsize=%d, i=%d \n", length, heapsize, i);
        maxHeapify(A, heapsize, length, i);
    }
}