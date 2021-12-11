#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

struct SubMove {
    std::string direction;
    int amount;
};

std::vector<SubMove> slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<SubMove> input;
    
    std::string direction;
    int number;

    while (file >> direction >> number) {
	SubMove mv = {
	    direction,
	    number
	};
	
	input.emplace_back(mv);
    }
    
    file.close();
    return input;
}

void change_pos(SubMove mv, int& hpos, int& vpos, int& aim)
{
    switch (mv.direction[0]) {
	case 'f':
	    hpos += mv.amount;
	    vpos += aim * mv.amount;
	    break;

	case 'd':
	    aim += mv.amount;
	    break;
	    
	case 'u':
	    aim -= mv.amount;
	    break;
    }
}

int main()
{
    std::vector<SubMove> input = slurp_input("../input.txt");
    int hpos = 0;
    int vpos = 0;
    int aim = 0;
    
    for (const SubMove& mv : input) {
	change_pos(mv, hpos, vpos, aim);
    }

    printf("%d\n", hpos * vpos);
    return 0;
}
