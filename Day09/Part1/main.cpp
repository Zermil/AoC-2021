#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<std::vector<int>> numbers;
    
    std::string line;
    while (std::getline(file, line)) {
	std::vector<int> acc;
	
	for (const char& c : line) {
	    acc.emplace_back(c - '0');
	}

	numbers.emplace_back(acc);
    }
    
    file.close();
    return numbers;
}

bool is_lowest_point(const std::vector<std::vector<int>>& board, int row, int col)
{
    const int neighbours[4][2] = {
	{ row + 1, col     },
	{ row - 1, col     },
	{ row,     col + 1 },
	{ row,     col - 1 }
    };
    
    for (const auto& neighbour : neighbours) {
	int new_row = neighbour[0];
	int new_col = neighbour[1];

	// Skip invalid.
	if (new_row < 0 || new_row > (int)board.size() - 1
	    || new_col < 0 || new_col > (int)board[row].size() - 1)
	    continue;
        
	if (board[new_row][new_col] <= board[row][col])
	    return false;
    }
    
    return true;
}

int main()
{
    const std::vector<std::vector<int>> input = slurp_input("../input.txt");
    
    std::vector<int> lowest_points;
    int answer = 0;

    for (size_t i = 0 ; i < input.size(); ++i) {
	for (size_t j = 0 ; j < input[i].size(); ++j) {
	    if (is_lowest_point(input, i, j)) {
		lowest_points.emplace_back(input[i][j] + 1);
	    }
	}
    }

    for (const int& n : lowest_points) {
	answer += n;
    }
    
    printf("%d\n", answer);
    return 0;
}
