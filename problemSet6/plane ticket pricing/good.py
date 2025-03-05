from functools import lru_cache

# @lru_cache(maxsize=None)
# def dp(idx, rem):
#     if idx == W + 1:
#         return 0

#     result = 0
#     for price, seat in zip(prices[idx], seats[idx]):
#         if seat <= rem:
#             result = max(result, seat * price + dp(idx + 1, rem - seat))
#         else:
#             result = max(result, rem * price)
#     return result

# N, W = map(int, input().split())
# # print("N: ", N)
# # print("W: ", W)

# prices = []
# seats = []

# for week in range(W + 1):
#     line = list(map(int, input().split()))
#     prices.append(line[1:1 + line[0]])
#     seats.append(line[1 + line[0]:])
#     # print("\nline: ",line)
#     # print("prices: ",prices)
#     # print("seats: ",seats)
    
# # print("prices: ",prices)
# # print("seats: ",seats)
    
# total_profit = dp(0, N)
# print(total_profit)
# for price, seat in zip(prices[0], seats[0]):
#     profit = min(seat, N) * price
#     if dp(1, N - min(seat, N)) + profit == total_profit:
#         print(price)
#         break


# second implementation
seats , lines = input().split()

lines = int(lines) + 1
seats = int(seats)

cache = {}

Combination = []

for i in range(lines):
    current = input().split()
    #int(current)
    PT =[]
    for j in range(int(current[0])):
        PT.append([int(current[j+1]), int(current[int(current[0]) + j + 1])])
    Combination.append(PT)

# print(Combination)
start = 0

def solution(seats, weeks):
    global start

    if ((seats,weeks)) in cache: return cache[(seats,weeks)]

    if (weeks == 0): return 0

    if (seats == 0): return 0

    CurrentWeek = lines - weeks    
    
    summationList = []

    for i in range(len(Combination[CurrentWeek])):
        
        if (seats >= Combination[CurrentWeek][i][1]):

            NewSeats = seats - Combination[CurrentWeek][i][1] 
            summation = Combination[CurrentWeek][i][0] * Combination[CurrentWeek][i][1] + solution(NewSeats, weeks-1) 
            summationList.append([summation,Combination[CurrentWeek][i][0]])
        
        else:
            summation = Combination[CurrentWeek][i][0] * seats + solution(0, weeks-1)
            summationList.append([summation,Combination[CurrentWeek][i][0]]) 
            #seats = 0
    #print(summationList)
    
    balls = max(summationList, key = lambda x:x[0])
    
    cache[seats, weeks] = balls[0]
    
    start = balls[1]

    return balls[0]

    
print(solution(seats, lines))
print(start)
    
