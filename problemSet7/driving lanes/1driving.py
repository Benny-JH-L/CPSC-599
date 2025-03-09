
def min_distance(n, m, k, r, straightaways, curves):
    # Initialize DP table
    dp = [[float('inf')] * (m + 1) for _ in range(n + 1)]
    dp[0][1] = 0  # Start in lane 1

    for i in range(1, n + 1):
        L = straightaways[i - 1]
        # Process straightaway
        for j in range(1, m + 1):
            if dp[i - 1][j] != float('inf'):
                # Stay in the same lane
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + L)
                # Change to adjacent lanes
                if j > 1:
                    dp[i][j - 1] = min(dp[i][j - 1], dp[i - 1][j] + L + r)
                if j < m:
                    dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j] + L + r)
        
        # Process curve
        if i < n:
            s, c = curves[i - 1]
            for j in range(1, m + 1):
                if dp[i][j] != float('inf'):
                    dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + s + c * j)

    return dp[n][1]

# Example usage:
n, m = 4, 3
k, r = 5, 2
straightaways = [10, 10, 10, 10]
# curves = [(4, -1), (4, -1), (4, 1)]
curves = [(10, -3), (10, -3), (10, 1)]

print(min_distance(n, m, k, r, straightaways, curves))  # Output the minimum distance

