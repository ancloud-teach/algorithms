/*
** [选择排序]
for i = 1 to A.length-1
    min = i
    for j = i+1 to A.length
        if A[j] < A[min]
            min = j
    temp = A[i]
    A[i] = A[min]
    A[min] = temp    
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <malloc.h>

#include "../../init.h"

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

        int inum = 0;
        start = clock(); 

        for (int i=0; i < len-1; i++) {
            int min = i;
            for (int j = i+1; j < len; j++) {
                if (A[j] < A[min])
                    min = j;
                ++inum;
            }

            int temp;
            temp = A[i];
            A[i] = A[min];
            A[min] = temp;
        }

#if 0
        printf("rst: ");
        for (int i=0; i<len; i++) {
            printf("%d ", A[i]);
        }
        printf("\n");
#endif

        finish = clock(); 
        duration = (double)(finish - start) / CLOCKS_PER_SEC;  
        printf("[%d]exec time: %f sec, exec:step=%d\n", iavg, duration, inum);

        avgDur += duration;
    }

    printf("average time: %f\n", avgDur/avgNum);
}

