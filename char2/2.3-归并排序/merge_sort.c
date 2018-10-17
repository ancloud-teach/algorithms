/*
** [分治法]
MERGW(A, p, q, r)
    n1 = q - p + 1
    n2 = r - p
    let L[1..n1+1] and R[1..n2+1] be new arrays
    for i = 1 to n1
        L[i] = A[p + i - 1]
    for j = 1 to n2
        R[j] = A[q + j]
    L[n1 + 1] = 无穷大
    R[n2 + 1] = 无穷大
    i = 1
    j = 1
    for k = p to r
        if L[i] <= R[j]
            A[k] = L[i]
            i = i + 1
        else
            A[K] = R[j]
            j = j + 1

MERGE-SORT(A, p, r)
    if p < r
        q = (p + r)/2
        MERGE-SORT(A, p, q)
        MERGE-SORT(A, q+1, r)
        MERGE(A, p, q, r)
*/  

#include <math.h>
#include <malloc.h>
#include <string.h>

int *tmpBufp;
int istep = 0;

void merge(int A[], int p, int q, int r)
{
    int const n1 = q - p + 1;
    int const n2 = r - q;

    int * L = tmpBufp;
    int * R = tmpBufp + n1;
    memcpy(L, A+p, sizeof(int)*n1);
    memcpy(R, A+q+1, sizeof(int)*n2);

    for (int i=0, j=0, k=p; k<=r; k++) {
        istep++;

        if (i >= n1)
            A[k] = R[j++];
        else if (j >= n2) 
            A[k] = L[i++];
        else if (L[i] <= R[j])
            A[k] = L[i++];
        else 
            A[k] = R[j++];
    }
}

void merge_sort(int A[], int p, int r) 
{
    if (p < r) {
        int q = (p + r) / 2;

        merge_sort(A, p, q);
        merge_sort(A, q+1, r);
        merge(A, p, q, r);
    }
}