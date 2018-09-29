/*
** [插入排序-递归]
INSERT-SORT(A, length)
    if length > 1 
        INSERT-SORT(A, length - 1)
    
    key = A[length]
    i = length - 1
    while i > 0 and A[i] > key
        A[i+1] = A[i]
        i = i + 1
    A[i+1] = key
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../../init.h"

int istep = 0;

void insertSort(int A[], int length)
{
    int key = A[length - 1];
    if (length > 2) 
       insertSort(A, length - 1);
    
    int i = length - 2;
    while (i >= 0 && A[i] > key){
        A[i+1] = A[i];
        i = i - 1;

        istep++;
    } 
    A[i+1] = key;
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

        insertSort(A, len);

        finish = clock(); 

#if 0
        printf("rst: ");
        for (int i=0; i<len; i++) {
            printf("%d ", A[i]);
        }
        printf("\n");
#endif

        duration = (double)(finish - start) / CLOCKS_PER_SEC;  
        printf("[%d]exec time: %f sec, exec:step=%d\n", iavg, duration, istep);

        avgDur += duration;
    }

    printf("average time: %f\n", avgDur/avgNum);
}
