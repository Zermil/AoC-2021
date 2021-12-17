#include <cstdio>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

struct Line {
    int x[2];
    int y[2];
};

int svtoi(std::string_view str)
{
    int output = 0;

    for (const char& c : str) {
	output = (output * 10) + c - '0';
    }

    return output;
}

std::vector<Line> slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<Line> lines;
    std::string line;
    
    while (std::getline(file, line)) {
	Line line_obj = {};

	std::string_view view = std::string_view(line);
	std::string_view first = view.substr(0, view.find_first_of(' '));
	std::string_view second = view.substr(view.find_last_of(' ') + 1);

	line_obj.x[0] = svtoi(first.substr(0, first.find_first_of(',')));
	line_obj.y[0] = svtoi(first.substr(first.find_first_of(',') + 1));

	line_obj.x[1] = svtoi(second.substr(0, second.find_first_of(',')));
	line_obj.y[1] = svtoi(second.substr(second.find_first_of(',') + 1));

	lines.emplace_back(line_obj);
    }
    
    file.close();
    return lines;
}

inline int abs(int x) { return x < 0 ? -x : x; }
static constexpr int BOARD_SIZE = 1024;

int main()
{
    std::vector<Line> input = slurp_input("../input.txt");
    int *board = new int[BOARD_SIZE * BOARD_SIZE]{};
        
    for (const Line& line : input) {
	if (line.x[0] != line.x[1] && line.y[0] != line.y[1])
	    continue;
	
	board[line.y[0] + line.x[0] * BOARD_SIZE]++;
	board[line.y[1] + line.x[1] * BOARD_SIZE]++;
	
	if (line.x[0] == line.x[1]) {
	    int dy = line.y[0] - line.y[1];
	    int sign = dy < 0 ? 1 : -1;

	    for (int i = 1; i < abs(dy); ++i) {
		board[(line.y[0] + (sign * i)) + (line.x[0] * BOARD_SIZE)]++;
	    }
	} else {
	    int dx = line.x[0] - line.x[1];
	    int sign = dx < 0 ? 1 : -1;

	    for (int i = 1; i < abs(dx); ++i) {
		board[line.y[0] + ((line.x[0] + (sign * i)) * BOARD_SIZE)]++;
	    }
	}
    }

    int overlap = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
	for (int j = 0; j < BOARD_SIZE; ++j) {
	    if (board[j * BOARD_SIZE + i] > 1)
		overlap++;
	}
    }

    delete[] board;
    printf("Overlap: %d\n", overlap);
    return 0;
}
