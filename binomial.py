
# Dynamic programming for calculating binmoal coefficient

import sys

n, k = map(int, sys.stdin.readline().split())

# 1 way
# cache[n][k] = (n choose k)
# cache = [[-1 for i in range(k+1)] for j in range(n+1)]
# def binom(n, k):
    
#     if (cache[n][k] != -1):
#         return cache[n][k]
    
#     if k == 0:
#         return 1
#     elif n == k:
#         return 1
#     result = binom(n-1, k) + binom(n-1, k-1) 
#     cache[n][k] = result # store the computed (n choose k)
#     return result
# you can optimize this a bit more, as it still repeats some calculations because of how this is written

# 2nd way ()
# cache[n][k] = (n choose k)
cache = [[0 for i in range(k+1)] for j in range(n+1)]
# store base cases in cache 
for i in range(n+1):
    cache[i][0] = 1

for i in range(n+1):
    cache[i][i] = 1 

for i in range(n+1):
    for j in range(i):
        cache[i][j] = cache[i-1][j-1] + cache[i-1][j]

