#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

std::vector<int> slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    
    std::vector<int> out;
    
    for (const char& c : line) {
	if (c == ',') continue;
	out.emplace_back(c - '0');
    }
    
    file.close();
    return out;
}

typedef unsigned long long ull;
int main()
{
    std::vector<int> input = slurp_input("../input.txt");
    ull current[9] = {};
    ull next[9] = {};
    
    for (const int& count : input) {
	current[count]++;
    }

    for (size_t i = 0; i < 256; ++i) {
	for (size_t j = 1; j < 9; ++j) {
	    next[j - 1] = current[j];
	}

	next[8] = current[0];
	next[6] += current[0];

	memcpy(current, next, sizeof(next));
    }
    
    ull answer = 0;
    for (const ull& num_of_fish : current) {
	answer += num_of_fish;
    }
    
    printf("%lld\n", answer);
    return 0;
}
