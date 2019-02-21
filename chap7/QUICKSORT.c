#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include "../init.h"
#include "QUICKSORT.h"


extern int istep;


/*
QUICKSORT(A, p, r)
	if (p < r)
		q = PARTITION(A, p, r)
		QUICKSORT(A, p, q-1)
		QUICKSORT(A, q+1, r)
    
 *
 * @p, start at 0
 * @r, start at 0
 */
void quicksort(AData A[], int p, int r)
{
	if (p >= r)
		return ;
	
	int q = 0;
	q = partition(A, p, r);
	if (q < 0)
		return ;
	quicksort(A, p, q-1);
	quicksort(A, q+1, r);
}


/* 
 PARTITION(A, p, r)
 	x = A[r]
 	i = p - 1
 	for j = p to r-1
 		if A[j] <= x
 			i = i+1
 			exchange A[i] to A[j]
 	exchange A[i+1] with A[r]
 	return i+1

 *
 * @p, start at 0
 * @r, start at 0
 */ 
int partition(AData A[], int p, int r)
{
	if (p >= r)
		return -1;
	
	AData x = A[r];
	AData tmp;
	int i = p - 1;
	for (int j = p; j <= r-1; j++) {
		if (A[j].value <= x.value) {
			i++;
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
			istep++;
		}
	}

	tmp = A[i+1];
	A[i+1] = A[r];
	A[r] = tmp;

	return i+1;
}