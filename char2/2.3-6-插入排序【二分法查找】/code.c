/*
** [插入排序-二分法查找]
FIND(A, head, tail, key)
    if (tail - head + 1) > 2
        half = (tail - head + 1) / 2 + head
        if A[half] == key
            pos = half
        else if A[half] > key
            pos = FIND(A, haed, half, key)
        else
            pos = FIND(A, half, tail, key)
    else 
        if key < A[head]
            pos = head
        else
            pos = tail
    return pos

FIND-SORT(A)
    for j=2 to A.length
        key = A[j]
        pos = FIND(A, 1, j-1, key)
        i = j
        while (i > pos)
            A[i] = A[i - 1]
        A[pos] = key
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../../init.h"

int istep = 0;

int find(int A[], int head, int tail, int key)
{
    int pos;
    if ((tail - head + 1) > 2) {
        int half = (tail - head + 1) / 2 + head;
        if (A[half] == key)
            pos = key;
        else  if (A[half] > key)
            pos = find(A, head, half-1, key);
        else 
            pos = find(A, half+1, tail, key);
    } else {
        if (key < A[head])
            pos = head;
        else 
            pos = tail;
    }

    return pos;
}

void findInsertSort(int A[], int len)
{
    for (int j=2; j<len; j++) {
        int key = A[j];
        int pos = find(A, 0, j-1, key);
        int i = j;
        while (i >= pos){
            A[i] = A[--i];
            istep++;
        }
        A[pos] = key;
    }

}

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("You should key in: %s <A.length, it is power(10, x)> <average num>\n", argv[0]);
        return -1;
    }

    int powNum = atoi(argv[1]);
    int avgNum = atoi(argv[2]);
    int maxNum = (int)pow(10, powNum);
    printf("cal num:%d averarg num:%d\n", maxNum, avgNum);
    
    int const size = sizeof(int) * maxNum;
    int *A = (int*)malloc(size);
    int *bkp = (int*)malloc(size);
    init(bkp, maxNum);

    clock_t start, finish;  
    double duration, avgDur=0.0;  

    int len = maxNum;

    for (int iavg=0; iavg<avgNum; iavg++) {
        memcpy(A, bkp, size);
        istep = 0;

        start = clock(); 

        findInsertSort(A, len);

        finish = clock(); 

#if 0
        printf("rst: ");
        for (int i=0; i<len; i++) {
            printf("%d, ", A[i]);
        }
        printf("\n");
#endif

        duration = (double)(finish - start) / CLOCKS_PER_SEC;  
        printf("[%d]exec time: %f sec, exec:step=%d\n", iavg, duration, istep);

        avgDur += duration;
    }

    printf("average time: %f\n", avgDur/avgNum);
}

