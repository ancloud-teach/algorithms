/*
** [分治法]
MERGW(A, p, q, r)
    n1 = q - p + 1
    n2 = r - p
    let L[1..n1+1] and R[1..n2+1] be new arrays
    for i = 1 to n1
        L[i] = A[p + i - 1]
    for j = 1 to n2
        R[j] = A[q + j]
    i = 1
    j = 1
    for k = p to r
        if i >= n1 or 
            A[k] = R[j]
            j = j + 1
        else if j >= n2
            A[k] = L[i]
            i = i + 1
        else if L[i] <= R[j]
            A[k] = L[i]
            i = i + 1
        else
            A[K] = R[j]
            j = j + 1

MERGE-SORT(A, p, r)
    if p < r
        q = (p + r)/2
        MERGE-SORT(A, p, q)
        MERGE-SORT(A, q+1, r)
        MERGE(A, p, q, r)
*/  
