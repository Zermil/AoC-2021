#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<int> numbers;
    int number;

    while (file >> number) {
	numbers.emplace_back(number);
    }
    
    file.close();
    return numbers;
}

int main()
{
    std::vector<int> input = slurp_input("../input.txt");
    int answer = 0;
    
    for (size_t i = 0; i < input.size() - 3; ++i) {
	int previous = input[i] + input[i + 1] + input[i + 2];
	int current = input[i + 1] + input[i + 2] + input[i + 3];
        
	if (current > previous) {
	    answer++;
	}
    }
    
    printf("%d\n", answer);
    return 0;
}
