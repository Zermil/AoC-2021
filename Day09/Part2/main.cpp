#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// Forward declaration.
std::vector<std::vector<int>> slurp_input(const std::string&);

const std::vector<std::vector<int>> input = slurp_input("../input.txt");
std::vector<std::vector<bool>> visited(input.size(), std::vector<bool>(input[0].size(), false));

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

bool is_lowest_point(int row, int col)
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
	if (new_row < 0 || new_row > static_cast<int>(input.size() - 1)
	    || new_col < 0 || new_col > static_cast<int>(input[row].size() - 1))
	    continue;
        
	if (input[new_row][new_col] <= input[row][col])
	    return false;
    }
    
    return true;
}

void find_basin(int row, int col, int& length)
{
    if (input[row][col] == 9 || visited[row][col])
	return;
    
    const int neighbours[4][2] = {
	{ row + 1, col     },
	{ row - 1, col     },
	{ row,     col + 1 },
	{ row,     col - 1 }
    };

    length++;
    visited[row][col] = true;
    
    for (const auto& neighbour : neighbours) {
	int new_row = neighbour[0];
	int new_col = neighbour[1];

	// Skip invalid.
	if (new_row < 0 || new_row > static_cast<int>(input.size() - 1)
	    || new_col < 0 || new_col > static_cast<int>(input[row].size() - 1))
	{
	    continue;
        }
	
	find_basin(new_row, new_col, length);
    }
}

int main()
{
    std::vector<int> basin_length;

    for (size_t i = 0 ; i < input.size(); ++i) {
	for (size_t j = 0 ; j < input[i].size(); ++j) {
	    if (is_lowest_point(i, j)) {
		int length = 0;
		find_basin(i, j, length);
		basin_length.emplace_back(length);		
	    }
	}
    }
    
    /* Note(Aiden): This whole thing could potentially be omitted
       it would require a different approach to inserting lengths
       or comparing them on the fly.
    */
    std::sort(basin_length.begin(), basin_length.end(), [](int a, int b) { return a > b; });    
    printf("%d\n", basin_length[0] * basin_length[1] * basin_length[2]);
    
    return 0;
}
