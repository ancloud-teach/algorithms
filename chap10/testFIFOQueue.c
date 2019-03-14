#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "../init.h"
#include "./FIFO-QUEUE.h"
#include "./STACK2QUEUE.h"
#include "./FIFO-SLIST.h"

#define QUEUE_SIZE        5
//Queue<AData> *gQueuep = NULL;
//Stack2Queue<AData> *gQueuep = NULL;
FIFOSlist<AData> *gQueuep = NULL;


void * thr_runTask(void *arg)
{
    int sleepTime = *(int*)arg;
    printf("runTask sleeptime: %d\n", sleepTime);

    while(1) 
    {
        sleep(sleepTime);
        printf("runTask acked.!!!\n");
        
        AData *datap  = gQueuep->dequeue() ;
        if (NULL == datap) {
            printf("Failed dequeue data from queue!!!\n");
            continue;
        }
        printf("dequeue data: %d\n\n", datap->value);
        free(datap);
        
        //printf("LIFO queue pop min: %d, other data:%d\n", min.value, min.index);
        //printData(gData, gHeapSize);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("You should key in: %s <the runTask sleep time(s)>\n", argv[0]);
        return -1;
    }
    int sleepTime = atoi(argv[1]);

    printf("You can key in the value, which you would be push in\n");
    char line[256];
    char *str = NULL;
    int index=0, value = 0;

	//gQueuep = new Queue<AData>(QUEUE_SIZE);
	//gQueuep = new Stack2Queue<AData>(QUEUE_SIZE);
	gQueuep = new FIFOSlist<AData>(QUEUE_SIZE);

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
        } else {
            value = atoi(line);
            printf("enqueue value=%d + \n", value);
            AData *insertp = (AData*)malloc(sizeof(AData));
            insertp->index = 0;
            insertp->value = value;
			if (gQueuep->enqueue(insertp) == NULL ) {
                printf("Faild enqueue value(%d) into queue!!!\n", value);
            }
        }

        //printData(gData, gHeapSize);
        printf("\n");
    }
}
