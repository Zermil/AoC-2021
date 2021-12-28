#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

enum Axis {
    X = 0,
    Y,
};

struct Point {
    int x;
    int y;
};

struct Fold {
    Axis axis;
    int amount;
};

std::vector<Point> points;
std::vector<Fold> folds;

size_t board_row = 2048;
size_t board_col = 2048;
bool board[2048][2048];

void slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    
    int max_x = -1;
    int max_y = -1;

    while (getline(file, line)) {
        // Folds starting.
        if (line == std::string())
            break;

        auto comma = line.find_first_of(',');
        int px = stoi(line.substr(0, comma));
        int py = stoi(line.substr(comma + 1));

        max_y = std::max(max_y, py);
        max_x = std::max(max_x, px);
        
        Point p = { px, py };
        points.emplace_back(p);
    }

    /* Note(Aiden): Has to include the last element
       if max_x = 14 then the range is 0...14
       not 0...13(!)
    */
    board_row = max_y + 1;
    board_col = max_x + 1;
    
    for (const Point& p : points) {
        board[p.y][p.x] = true;
    }

    // Parse folds.
    while (getline(file, line)) {
        auto equal = line.find_first_of('=');
        Axis axis = static_cast<Axis>(line.substr(equal - 1, 1)[0] - 'x');
        int amount = stoi(line.substr(equal + 1));

        Fold f = { axis, amount };
        folds.emplace_back(f);
    }
    
    file.close();
}

void fold_board(Fold inst)
{
    switch (inst.axis) {
        case X: {
            for (size_t row = 0; row < board_row; ++row) {
                for (size_t col = inst.amount + 1; col < board_col; ++col) {
                    if (board[row][col]) {
                        int new_col = inst.amount - (col - inst.amount);
                        board[row][col] = false;
                        board[row][new_col] = true;
                    }
                }
            }

            board_col = inst.amount;
        } break;
            
        case Y: {
            for (size_t row = inst.amount + 1; row < board_row; ++row) {
                for (size_t col = 0; col < board_col; ++col) {
                    if (board[row][col]) {
                        int new_row = inst.amount - (row - inst.amount);
                        board[row][col] = false;
                        board[new_row][col] = true;
                    }
                }
            }

            board_row = inst.amount;
        } break;
    }
}

int main()
{
    slurp_input("../input.txt");

    for (const Fold& f : folds) {
        fold_board(f);
    }

    for (size_t row = 0; row < board_row; ++row) {
        for (size_t col = 0; col < board_col; ++col) {
            printf(board[row][col] ? "#" : " ");
        }

        printf("\n");
    }

    return 0;
}
