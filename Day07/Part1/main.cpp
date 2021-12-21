#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

std::vector<int> slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<int> numbers;
    
    int number;
    char comma;
    
    while (file >> number >> comma) {
	numbers.emplace_back(number);
    }

    // EOF
    numbers.emplace_back(number);

    file.close();
    return numbers;
}

int max_in_vector(const std::vector<int>& vec)
{
    int max = -1;
    
    for (const int& num : vec) {
	if (num > max)
	    max = num;
    }
    
    return max;
}

inline int abs(int x) { return x < 0 ? -x : x; }

int main()
{
    std::vector<int> input = slurp_input("../input.txt");
    int max = max_in_vector(input);
    int desired = 0;
    int fuel_cost = INT_MAX;
    
    for (int i = 0; i < max; ++i) {
	int sum = 0;
	
	for (const int& pos : input) {
	    sum += abs(pos - desired);
	}

	if (sum < fuel_cost)
	    fuel_cost = sum;

	desired++;
    }

    printf("%d", fuel_cost);
    return 0;
}
