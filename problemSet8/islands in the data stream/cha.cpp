#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

int islands_of_length_n(const std::vector<int>& lis, int n) {
    int s = 0;
    for (int i = 1; i < lis.size() - n; i++) {
        int max_boundary = std::max(lis[i-1], lis[i+n]);
        int min_island = *std::min_element(lis.begin() + i, lis.begin() + i + n);
        
        if (max_boundary < min_island) {
            s += 1;
        }
    }
    return s;
}

int islands(const std::vector<int>& lis) {
    int sum = 0;
    for (int n = 1; n <= 10; n++) {
        sum += islands_of_length_n(lis, n);
    }
    return sum;
}

int main() {
    int t;
    std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        std::string line;
        std::cin.ignore(); // Clear the newline character
        std::getline(std::cin, line);
        
        std::vector<int> numbers;
        std::istringstream iss(line);
        int num;
        while (iss >> num) {
            numbers.push_back(num);
        }
        
        std::cout << (i + 1) << " " << islands(numbers) << std::endl;
    }
    
    return 0;
}
