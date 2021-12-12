#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<std::string> input;
    std::string number;

    while (file >> number) {        
	input.emplace_back(number);
    }
    
    file.close();
    return input;
}

int main()
{
    std::vector<std::string> input = slurp_input("../input.txt");

    // All binary numbers are the same length, so we can just take the length
    // of the first one.
    const size_t number_len = input[0].length();
    
    int gamma = 0b0;
    int epsilon = 0b0;
    for (size_t i = 0; i < number_len; ++i) {	    
	int ones = 0;
	int zeros = 0;
	
	for (size_t j = 0; j < input.size(); ++j) {
	    switch (input[j][i]) {
		case '1':
		    ones++;
		    break;

		case '0':
		    zeros++;
		    break;
	    }
	}

	if (ones > zeros) {
	    gamma |= (0b1 << (number_len - (i + 1)));
	} else {
	    epsilon |= (0b1 << (number_len - (i + 1)));
	}
    }

    printf("%d\n", gamma * epsilon);
    return 0;
}
