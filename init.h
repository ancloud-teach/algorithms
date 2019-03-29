#ifndef _ALGOR_INIT_
#define _ALGOR_INIT_

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

struct Data {
    struct Data *nextp;
    int value;
    int index;
};

typedef struct Data AData;
#define ADATA_SIZE      sizeof(AData)

#define ARRAY_NIL       -1

#define APLOG(fmt,...)  \
  do { if (1) fprintf(stdout, "[APLOG]%s:%d "fmt, __FILE__,__LINE__, ##__VA_ARGS__); } while (0)

inline void init(AData A[], int const maxNum, bool bdescend)
{
    time_t tm;
    
    time(&tm);
    srand((unsigned int )tm);
   
    //printf("data init: ");
    for (int i=0; i<maxNum; i++) {
        A[i].value = bdescend != false ? maxNum-i : i+1;
        //printf("%d, ", A[i].value);
    }
    //printf("\n\n");  
}

inline void printData(AData data[], int heapSize)
{
    for (int i=0; i<heapSize; i++) {
        printf ("No.%03d val=%d, index=%d\n", i, data[i].value, data[i].index);
    }
}

#endif