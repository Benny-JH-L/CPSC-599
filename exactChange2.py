
import sys

inf = 10e8

def exactChange(target, current_coin):
    
    if (target == 0):
        return (0,0)
    
    elif (current_coin >= n_coins):
        return (inf, 0)
    else:
        dontuse = exactChange(target, current_coin + 1)
        
        if (coins[current_coin] > target):
            return (coins[current_coin] - target, 1)
        else:
            x = exactChange(target - coins[current_coin], current_coin + 1)
            paid = (x[0], x[1] + 1)
            
        if (paid[0] < dontuse[0]):
            return paid
        elif (dontuse[0] < paid[0]):
            return dontuse
        else:
            if (paid[1] <= dontuse[1]):
                return paid
            else:
                return dontuse

# parse input
buff = sys.stdin.read().split()
n_cases = int(buff[0])
index = 1

