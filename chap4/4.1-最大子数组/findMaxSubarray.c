/*
** [查找最大子数组]

1. 查找跨越分割点的最大子数组
FIND-MAX-CROSSING-SUBRARRAY(A, low, mid, high)
    lef-sum = -/8
    sum = 0
    for i = mid downto mid
        sum = sum + A[i]
        if sum > left-sum
            left-sum = sum
            max-left = i
    rigth-sum = -/8
    sum = 0
    for j = mid+1 downto high
        sum = sum + A[j]
        if sum > right-sum
            right-sum = sum
            max-right = j
    return (max-left, max-right, lef-sum + right-sum)

2. 查找最大子数组 
FIND-MAX-SUBARRAY(A, low, high)
    if high == low
        return (low, high, A[low])
    else mid = [low + high]/2
        (left-low, left-high, lef-sum) = 
            FIND-MAX-SUBARRAY(A, low, mid)
        (right-low, right-high, right-sum) = 
            FIND-MAX-SUBARRAY(A, mid+1, right)
        (cross-low, cross-high, cross-sum) = 
            FIND-MAX-CROSSING-SUBRARRAY(A, low, mid, high)
        
        if lef-sum >= right-sum and lef-sum >= cross-sum
            return (left-low, left-high, lef-sum) 
        elseif right-sum >= lef-sum and right-sum >= cross-sum
            return (right-low, right-high, right-sum)
        else 
            return (cross-low, cross-high, cross-sum)
*/      
