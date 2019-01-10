#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "../init.h"

extern AData heapMax(AData A[]);
extern AData heapExtractMax(AData A[], int const len, int * heapsizep);
extern void heapIncreaseKey(AData A[], int i, AData key);
extern void maxHeapInsert(AData A[], AData key, int *heapsizep);

#define LEN_ADTA        100
AData gData[LEN_ADTA];
int gHeapSize = 0;

void * thr_runTask(void *arg)
{
    int sleepTime = *(int*)arg;
    printf("runTask sleeptime: %d\n", sleepTime);

    while(1) 
    {
        sleep(sleepTime);
        printf("runTask acked.!!!\n\n");
        
        if (gHeapSize < 1) 
            continue;

        AData max = heapExtractMax(gData, LEN_ADTA, &gHeapSize);
        printf("heap extract max: %d, other data:%d\n", max.value, max.index);
        printData(gData, gHeapSize);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("You should key in: %s <the runTask sleep time(s)>\n", argv[0]);
        return -1;
    }
    int sleepTime = atoi(argv[1]);

    printf("You can key in: index=priority\n");
    char line[256];
    char *str = NULL;
    int index=0, pro = 0;

    pthread_t    tidRunTask;  
    int err = pthread_create(&tidRunTask, NULL, thr_runTask, &sleepTime);
    if (err != 0) {
        printf("ERROR: create thread thr_runTask error.\n");
    } 
    else {
        printf("thread thr_runTask is running\n");
    }

    while (1) {
        str = gets(line);
        if (str == NULL){
            continue;
        }
        printf("You key in: %s\n", line);
        if (!isdigit(line[0])) {
            //printf("You key in error(%s)\n", line);
        } else if (strchr(line, '=') != NULL) {
            sscanf(line, "%d=%d", &index, &pro);
            printf("index = %d, pro=%d\n", index, pro);
            AData increase = {
                pro, index
            };
            heapIncreaseKey(gData, index, increase);
        } else {
            pro = atoi(line);
            printf("insert pro=%d + \n", pro);
            AData insert = {
                pro, gHeapSize
            };
            maxHeapInsert(gData, insert, &gHeapSize);
        }

        printData(gData, gHeapSize);
        printf("\n");
    }
}