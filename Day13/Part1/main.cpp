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

/* Note(Aiden): You could find max X and Y values from a set of points
   using max and min functions/algorithms.
*/
constexpr size_t board_sz = 2048;
bool board[board_sz][board_sz] = { false };

void slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        // Folds starting.
        if (line == std::string())
            break;

        auto comma = line.find_first_of(',');
        int px = stoi(line.substr(0, comma));
        int py = stoi(line.substr(comma + 1));

        Point p = { px, py };
        points.emplace_back(p);
    }

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
            for (size_t row = 0; row < board_sz; ++row) {
                for (size_t col = inst.amount + 1; col < board_sz; ++col) {
                    if (board[row][col]) {
                        int new_col = inst.amount - (col - inst.amount);
                        board[row][col] = false;
                        board[row][new_col] = true;
                    }
                }
            }
        } break;
        case Y: {
            for (size_t row = inst.amount + 1; row < board_sz; ++row) {
                for (size_t col = 0; col < board_sz; ++col) {
                    if (board[row][col]) {
                        int new_row = inst.amount - (row - inst.amount);
                        board[row][col] = false;
                        board[new_row][col] = true;
                    }
                }
            }
        } break;
    }
}

int main()
{
    slurp_input("../input.txt");

    fold_board(folds[0]);
    int answer = 0;
    
    for (size_t row = 0; row < board_sz; ++row) {
        for (size_t col = 0; col < board_sz; ++col) {
            if (board[row][col]) answer++;
        }
    }

    printf("%d\n", answer);
    return 0;
}
