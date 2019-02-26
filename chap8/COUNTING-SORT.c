#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include "../init.h"
#include "COUNTING-SORT.h"


extern int istep;


/*
COUNTING-SORT(A, B, k)
	let C[0..k] be a new array
	for i=0 to k
		C[i] = 0
	for j=1 to A.length
		C[ A[j] ] = C[ A[j] ] + 1
	//- C[i] now contains the number of elements equal to i
	for i=1 to k
		C[i] = C[i] + C[i-1]
	//- C[i] now contains the number of elements less than or equan to i
	for j=A.length to downto 1
		B[ C[A[j]] ] = A[j]
		C[ A[j] ] = C[ A[j] ] - 1
    
 *
 * @A, the data would be sorted
 * @B, return the result
 * @Alen, the length of A
 * @k, the max number of element in A
 */
void counting_sort(AData A[], AData B[], int const Alen, int k)
{
	int *C = (int *)malloc(sizeof(int) * (k+1));
	for (int i=0; i<=k; i++) {
		C[i] = 0;
	}
	for (int j=0; j<Alen; j++) {
		C[ A[j].value ]++;
		istep++;
	}
	
	for (int i=1; i<=k; i++) {
		C[i] += C[i-1];
		istep++;
	}

	for (int j=Alen-1; j >= 0; j--) {
		B[ C[A[j].value] - 1] = A[j];
		C[A[j].value]--;
		istep++;
	}
	free(C);
}
