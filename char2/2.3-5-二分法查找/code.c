/*
** [二分法查找]
FIND(A, key)
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
