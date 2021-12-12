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

int bin_to_dec(const std::string& str)
{
    int bin = 0b0;

    for (const char& c : str) {
	if (c == '1') bin |= 0b1;
	bin <<= 1;
    }
    
    return bin >> 1;
}

std::vector<std::string> get_new_vector(const std::vector<std::string>& input, size_t pos, char comp)
{
    std::vector<std::string> filtered;
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i][pos] == comp) {
	    filtered.emplace_back(input[i]);
	}
    }

    return filtered;
}

std::string filter_values(std::vector<std::string> input, bool co2)
{
    size_t i = 0;
    char comp;

    while (input.size() != 1) {
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

	if (ones == zeros) {
	    comp = co2 ? '0' : '1';
	} else if (co2) {
	    comp = ones < zeros ? '1' : '0';
	} else {
	    comp = ones > zeros ? '1' : '0'; 
	}

	input = get_new_vector(input, i, comp);
	i++; // AFAIK based on Day03's description this will never overflow.
    }

    return input[0];
}

int main()
{
    std::vector<std::string> input = slurp_input("../input.txt");
    std::string co2 = filter_values(input, true);
    std::string oxygen = filter_values(input, false);

    int co2_dec = bin_to_dec(co2);
    int oxygen_dec = bin_to_dec(oxygen);
    
    printf("%d\n", co2_dec * oxygen_dec);
    return 0;
}
