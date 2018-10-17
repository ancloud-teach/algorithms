/*
** [求和查找-统计一个数的组合中，任意两个数相加等于另外一个数的个数]
PAIR-EXISTS (S, v)
    A = MERGE-SORT(S)

    for i = 1 to A.length 
        if BINARY-SEARCH(A+i+1, A[i]) != NIL
            return true
    return false
*/