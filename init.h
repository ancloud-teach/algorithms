#ifndef _ALGOR_INIT_
#define _ALGOR_INIT_

inline void init(int A[], int const maxNum)
{
    time_t tm;
    
    time(&tm);
    srand((unsigned int )tm);
   
    //printf("data init: ");
    for (int i=0; i<maxNum; i++) {
        A[i] = maxNum-i;
        //printf("%d, ", A[i]);
    }
    printf("\n\n");  
}

#endif