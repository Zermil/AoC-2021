#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

static std::vector<int> numbers_drawn;

struct Board {
    int numbers[5][5];
    bool checked;

    bool mark_board(int number) {
	for (size_t i = 0; i < 5; ++i) {
	    for (size_t j = 0; j < 5; ++j) {
		if (numbers[i][j] == number) {
		    numbers[i][j] = -1;
		    return true;
		}
	    }
	}

	return false;
    }

    bool bingo(int num) {
	if (checked || !mark_board(num)) {
	    return false;
	}

	for (size_t i = 0; i < 5; ++i) {
	    bool rows = numbers[i][0] + numbers[i][1] + numbers[i][2] + numbers[i][3] + numbers[i][4] == -5;
	    bool cols = numbers[0][i] + numbers[1][i] + numbers[2][i] + numbers[3][i] + numbers[4][i] == -5;
	    
	    if (rows || cols) {
		checked = true;
		return true;
	    }
	}

	return false;
    }

    int get_sum() {
	int sum = 0;
	
	for (size_t i = 0; i < 5; ++i) {
	    for (size_t j = 0; j < 5; ++j) {
		if (numbers[i][j] != -1) {
		    sum += numbers[i][j];
		}
	    }
	}

	return sum;
    }

    void display() {
	for (size_t i = 0; i < 5; ++i) {
	    printf("\n");
	    
	    for (size_t j = 0; j < 5; ++j) {
		printf("%d ", numbers[i][j]);
	    }
	}
    }
};

void set_numbers_drawn(const std::string& drawn)
{
    size_t beg = 0;
    size_t i = 0;
    
    for (; i < drawn.length(); ++i) {
	if (drawn[i] == ',') {
	    numbers_drawn.emplace_back(std::stoi(drawn.substr(beg, i - beg)));
	    beg = i + 1;
	}
    }

    // Catch last one.
    numbers_drawn.emplace_back(std::stoi(drawn.substr(beg, i - beg)));
}

std::vector<Board> slurp_input(const std::string& filename)
{
    std::ifstream file(filename);

    std::string drawn;
    std::getline(file, drawn);
    set_numbers_drawn(drawn);
    
    int a, b, c, d, e;
    
    Board board = {};
    board.checked = false;
    
    std::vector<Board> boards;

    int inserted = 0;
    while (file >> a >> b >> c >> d >> e) {
	if (inserted > 4) {
	    boards.emplace_back(board);
	    inserted = 0;
	}
	
	board.numbers[inserted][0] = a;
	board.numbers[inserted][1] = b;
	board.numbers[inserted][2] = c;
	board.numbers[inserted][3] = d;
	board.numbers[inserted][4] = e;
	
        inserted++;
    }

    // Catch at eof.
    boards.emplace_back(board);
    
    file.close();
    return boards;
}

int get_winning_board(int num, std::vector<Board>& input)
{
    int index = -1;
    
    for (size_t i = 0; i < input.size(); ++i) {
	if (input[i].bingo(num)) {
	    index = i;
	}
    }

    return index;
}

int main()
{
    std::vector<Board> input = slurp_input("../input.txt");

    int winning_index;
    int winning_number;

    for (const int& num : numbers_drawn) {
	int temp_index = get_winning_board(num, input);
	
	if (temp_index != -1) {
	    winning_index = temp_index;
	    winning_number = num;
	}
    }

    input[winning_index].display();
    printf("\n%d\n", input[winning_index].get_sum() * winning_number);

    return 0;
}
