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
    
    for (size_t i = 1; i < input.size(); ++i) {
	if (input[i] > input[i - 1]) {
	    answer++;
	}
    }
    
    printf("%d\n", answer);
    return 0;
}
