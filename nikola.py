import sys
N = int(input())

costs = []

for i in range(N):
    costs.append(int(sys.stdin.readline()))

INF = 500000
cache = [[0 for i in range(N+1)] for j in range(N+1)]

def jump(n, s):
    # DP check here
    
    if n == 1 and s == 1:
        return 0
    elif s == 1:
        INF

    if (n + (s-1) >= ):
        
        
