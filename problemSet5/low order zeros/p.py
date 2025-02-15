def last_nonzero_digit(n):
    if n < 10:
        return [1, 1, 2, 6, 4, 2, 2, 4, 2, 8][n]
    
    # Remove factors of 10 (i.e., 5s and corresponding 2s)
    num_fives = 0
    temp = n
    while temp:
        temp //= 5
        num_fives += temp
    
    # Compute product of all numbers mod 10 ignoring factors of 5
    product = 1
    for i in range(1, n + 1):
        num = i
        while num % 5 == 0:
            num //= 5  # Remove factors of 5
        product = (product * (num % 10)) % 10  # Compute mod 10
    
    # Adjust for extra 2s (each removed 5 had a paired 2)
    extra_twos = 2 ** num_fives
    product = (product * (extra_twos % 10)) % 10
    
    return product

n = 1000000
print(last_nonzero_digit(n))  # Example usage
