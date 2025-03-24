class DisjointSet:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
    
    def find(self, x):
        # Path compression
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        # Union by rank
        root_x = self.find(x)
        root_y = self.find(y)
        
        if root_x == root_y:
            return
        
        if self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        elif self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1
    
    def same_set(self, x, y):
        return self.find(x) == self.find(y)

def solve_disjoint_sets(n, operations):
    ds = DisjointSet(n)
    results = []
    
    for op in operations:
        op_type, a, b = op.split()
        a, b = int(a), int(b)
        
        if op_type == "=":
            ds.union(a, b)
        elif op_type == "?":
            if ds.same_set(a, b):
                results.append("yes")
            else:
                results.append("no")
    
    return results

# For testing with the sample inputs
def process_sample(sample_input):
    lines = sample_input.strip().split('\n')
    n, q = map(int, lines[0].split())
    operations = lines[1:q+1]
    return solve_disjoint_sets(n, operations)

# Sample Input 1
sample_input_1 = """10 4
? 1 3
= 1 8
= 3 8
? 1 3"""

# Sample Input 2
sample_input_2 = """4 5
? 0 0
= 0 1
= 1 2
= 0 2
? 0 3"""

# print("Sample Output 1:")
print('\n'.join(process_sample(sample_input_1)))

# print("\nSample Output 2:")
print('\n'.join(process_sample(sample_input_2)))
