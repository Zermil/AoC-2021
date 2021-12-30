#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <queue>

int board_sz = 512;
int board[512][512];

struct Point {
    int row;
    int col;
};

void slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    
    int size = 0;
    std::string line;
    
    while (getline(file, line)) {        
        for (size_t i = 0; i < line.length(); ++i) {
            board[size][i] = line[i] - '0';
        }
        
        size++;
    }

    board_sz = size;
    file.close();
}

inline index(int row, int col) { return row * board_sz + col; }

int main()
{
    slurp_input("../input.txt");
    
    constexpr int NBRS_CNT = 4;
    constexpr int NBRS[NBRS_CNT][2] = {
        { 1, 0 },
        { -1, 0 },
        { 0, 1 },
        { 0, -1 }
    };
    
    std::queue<Point> q;
    int *dist = (int*)alloca(sizeof(int) * board_sz * board_sz);
    
    for (int row = 0; row < board_sz; ++row) {
        for (int col = 0; col < board_sz; ++col) {
            dist[index(row, col)] = INT_MAX;
        }
    }

    Point p = { 0, 0 };
    q.emplace(p);
    dist[index(0, 0)] = 0;

    while (!q.empty()) {
        Point front = q.front();

        for (int i = 0; i < NBRS_CNT; ++i) {
            int row = front.row + NBRS[i][0];
            int col = front.col + NBRS[i][1];

            if (row < 0 || row > board_sz - 1 || col < 0 || col > board_sz - 1)
                continue;

            if (dist[index(front.row, front.col)] + board[row][col] < dist[index(row, col)]) {
                dist[index(row, col)] = dist[index(front.row, front.col)] + board[row][col];

                p.row = row;
                p.col = col;
                q.emplace(p);
            }
        }
        
        q.pop();
    }

    printf("%d\n", dist[index(board_sz - 1, board_sz - 1)]);
    
    return 0;
}
