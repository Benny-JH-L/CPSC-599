
import sys

found = set()

OFFSET = 3000

def count(index, par, val):
    
    if (cache[index][par][val + OFFSET] != -1):
        return
    if (index == n):
        found.add(val)
        return
    if (par % 2 == 0):
        newVal = val + nums[index]
    else:
        newVal = val - nums[index]
    
    if (nums[index] < 0):
        count(index + 1, par + 1, newVal)
    if (par > 0):
        count (index + 1, par - 1, newVal)
    count(index + 1, par, newVal)   
    
    cache[index][par][val + OFFSET] = 1

symbols = sys.stdin.readline().split()
nums = []

sign = 1
for s in symbols:
    if (s == '+'):
        sign = 1
    elif (s == '-'):
        sign = -1
    else:
        nums.append(sign * int(s))

print(nums)
n = len(nums)

# make a 3D array, but idk if i did it right :)
cache = [[[-1 for i in range(0, 6001)] for k in range(0, 6001)] for j in range(0, 6001)]

count(0,0,0)
