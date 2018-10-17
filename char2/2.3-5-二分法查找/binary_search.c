/*
** [二分法查找]
BINARY-SEARCH(A, key)
    head = 1
    tail = A.length
    while head < tail
        mid = (head + tail) / 2
        if A[mid] == key
            return mid
        else A[mid] > key
            tail = mid -1
        else
            head mid + 1
    return NIL
*/

// Indices in the C code are different
int binary_search(int A[], int length, int v) 
{
    int low  = 0;
    int high = length;

    int mid;
    while (low < high) {
        mid = (low + high) / 2;

        if (A[mid] == v)
            return mid;
        else if (A[mid] < v)
            low = mid + 1;
        else
            high = mid;
    }

    return -1;
}