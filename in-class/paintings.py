
import sys

inputs = sys.stdin.read().split('\n')

n = int(inputs[0])
colours = inputs[1].split()

m = int(inputs[2])
conflicts = []

for i in range(m):
    pair = inputs[3 + i].split()
    conflicts.append((pair[0], pair[1]))
    
print(colours)
print(conflicts)

# found is a flag to indicate whether we have found the first solution (best solution, favorite painting)
def colour(used, last, found):
    
    if (used == (1<<n)-1):
        if not found:
            print("Best solution found!")
            return (1, [last])
        return (1, [])
    
    total = 0
    colour_used = []
    
    # loop through all colours
    for i in range(n):
        # if used, then skip
        if (used & (1<<i)):
            continue
        if ((colours[i], last) in conflicts) or ((last, colours[i]) in conflicts):
            continue
        
        result = colour(used | (1 << i), colours[i])
        total += result[0]
        if (result[1]): # as long as its not an empty list
            found = True
            colour_used = [last] + result[1] 
        
    return (total, colour_used)

result = colour(0, "", False)
print(f"Colours count: {result[0]}")
print(f"optimal: {result[1]}")  # need to clean up "" string
