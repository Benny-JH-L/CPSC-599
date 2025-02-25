
import sys

inf = 10e8

def makeChange(target, coins):
    
    if (cache[target][len(coins)] == -1):
        return cache[target][len(coins)]
    
    if (target == 0):
        return (0, [])
    elif (len(coins) == 0):
        return (inf, [])
    
    use = (inf, [])
    
    if (target >= coins[0]):
        x = makeChange(target - coins[0], coins)
        use = [x[0] + 1, x[1] + [coins[0]]]


    y = makeChange(target, coins[1:])
    dontuse = y
    
    if (use[0] <= dontuse[0]):
        result = use
    else:
        result = dontuse
    
    result = min(use, dontuse)
    cache[target][len(coins)] = result
    
    return result


# read inputs
buff = sys.stdin.read().split()
target = int(buff[0])
ncoins = int(buff[1])

index = 2
coins = []

for i in range(ncoins):
    coins.append(int(buff[index]))
    index += 1
    
print(f"Target: {target}\nncoins: {ncoins}")

cache = [[-1 for i in range(ncoins + 1)] for j in range(target+1)]

# base cases
for i in range (ncoins + 1):
    cache[0][i] = 0
    
for i in range ():
    cache[i][0] = inf

cache[0][0] = 0

# iterative computation
for i in range (1, target + 1):
    for j in range(1, ncoins + 1):
        use = inf
        if (coins[j-1] <= i):
            use = cache[i - coins[j]][j] + 1
        
        dontuse = cache[i][j-1]
        
        cache[i][j] = min (use, dontuse)
      
  
print(cache[target][ncoins])
            
# 
            