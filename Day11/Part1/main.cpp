#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

int board[10][10];
bool octo_flash[10][10];
unsigned int flashes;

void slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    size_t index = 0;
    
    while (std::getline(file, line)) {
	for (size_t i = 0; i < line.length(); ++i) {
	    board[index][i] = line[i] - '0';
	}

	index++;
    }
    
    file.close();
}

void visit_neighbours(size_t row, size_t col)
{   
    if (octo_flash[row][col])
	return;

    flashes++;
    octo_flash[row][col] = true;
    
    for (int i = -1; i < 2; ++i) {
	for (int j = -1; j < 2; ++j) {
	    int new_row = row + i;
	    int new_col = col + j;

	    if (new_row < 0 || new_row > 9
		|| new_col < 0 || new_col > 9
		|| (i == 0 && j == 0))
	    {
		continue;
	    }

	    int& octopus = board[new_row][new_col];
	    octopus++;

	    if (octopus > 9)
		visit_neighbours(new_row, new_col);
	}
    }
}

void simulate_step()
{
    for (int row = 0; row < 10; ++row) {
	for (int col = 0; col < 10; ++col) {
	    if (octo_flash[row][col]) {
		octo_flash[row][col] = false;
		board[row][col] = 0;
	    }
	}
    }
    
    for (size_t row = 0; row < 10; ++row) {
	for (size_t col = 0; col < 10; ++col) {
	    int& octopus = board[row][col];
	    octopus++;
	    
	    if (octopus > 9)
		visit_neighbours(row, col);
	} 
    }
}

int main()
{   
    slurp_input("../input.txt");
    
    for (int i = 0; i < 100; ++i) {
	simulate_step();
    }
    
    printf("flashes: %d\n", flashes);
    return 0;
}
