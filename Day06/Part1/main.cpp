#include <cstdio>
#include <fstream>
#include <string>
#include <unordered_map>

std::string slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    
    std::string out = std::string();
    
    for (const char& c : line) {
	if (c == ',') continue;
	out += c;
    }
    
    file.close();
    return out;
}

std::unordered_map<char, char> outcomes = {
    { '8', '7' },
    { '7', '6' },
    { '6', '5' },
    { '5', '4' },
    { '4', '3' },
    { '3', '2' },
    { '2', '1' },
    { '1', '0' },
    { '0', '6' }
}; 

int main()
{
    std::string input = slurp_input("../input.txt");

    for (int i = 0; i < 80; ++i) {
	size_t current_length = input.length();

	for (size_t j = 0; j < current_length; ++j) {
	    char& fish = input[j];
	    char prev = fish;
	    fish = outcomes[fish];
	    
	    if (fish == '6' && prev == '0') {
		input += '8';
	    }
	}
    }

    printf("%lld\n", input.length());
    return 0;
}
