def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    idx = 0
    N = int(data[idx])
    W = int(data[idx+1])
    idx += 2
    
    estimates = []
    for _ in range(W+1):
        K = int(data[idx])
        idx += 1
        prices = list(map(int, data[idx:idx+K]))
        idx += K
        seats = list(map(int, data[idx:idx+K]))
        idx += K
        estimates.append((prices, seats))
    
    dp = [[-1 for _ in range(N+1)] for _ in range(W+1)]
    
    for s in range(N+1):
        dp[0][s] = 0
    
    for w in range(1, W+1):
        prices, seats = estimates[W - w]
        for s in range(N+1):
            max_revenue = -1
            for i in range(len(prices)):
                p = prices[i]
                sold = min(s, seats[i])
                revenue = p * sold + dp[w-1][s - sold]
                if revenue > max_revenue:
                    max_revenue = revenue
            dp[w][s] = max_revenue
    
    max_total_revenue = dp[W][N]
    
    current_price = 0
    s = N
    for w in range(W, 0, -1):
        prices, seats = estimates[W - w]
        for i in range(len(prices)):
            p = prices[i]
            sold = min(s, seats[i])
            if dp[w][s] == p * sold + dp[w-1][s - sold]:
                current_price = p
                s -= sold
                break
    
    print(max_total_revenue)
    print(current_price)

if __name__ == "__main__":
    main()