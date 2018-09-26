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

void init(int A[], int const maxNum)
{
    time_t tm;
    
    time(&tm);
    srand((unsigned int )tm);
    
    printf("data init: ");
    for (int i=0; i<maxNum; i++) {
        A[i] = rand() % maxNum;
        printf("%d ", A[i]);
    }
    printf("\n\n");
}

int main(int argc, char **argv)
{
    int maxNum = 100;
    if (argc != 1) {
        maxNum = atoi(argv[1]);
    }
    int A[maxNum];
    init(A, maxNum);

    clock_t start, finish;  
    double duration;  

    start = clock(); 

    int len = maxNum;
    int inum = 0;
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
    finish = clock();  
    duration = (double)(finish - start) / CLOCKS_PER_SEC;  

    printf("rst(exec:step=%d): ", inum);
    for (int i=0; i<len; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    printf("exec time: %f sec\n", duration);
}

