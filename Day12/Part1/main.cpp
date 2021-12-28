#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

typedef std::vector<std::vector<bool>> board;

constexpr size_t con_sz = 16;
bool visited[con_sz];
std::vector<std::string> unique;

// Forward declaration.
board slurp_input(const std::string&);
board connections = slurp_input("../input.txt");

size_t find(const std::string& name)
{
    for (size_t i = 0; i < unique.size(); ++i) {
        if (unique[i] == name)
            return i;
    }

    unique.emplace_back(name);
    return unique.size() - 1;
}

board slurp_input(const std::string& filename)
{
    std::ifstream file(filename);

    board slurped(con_sz, std::vector<bool>(con_sz, false));
    std::string line;
    
    while(getline(file, line)) {
        auto dash = line.find_first_of('-');
        std::string name = line.substr(0, dash);
        std::string connection = line.substr(dash + 1);

        size_t index_a = find(name);
        size_t index_b = find(connection);

        slurped[index_a][index_b] = true;
        slurped[index_b][index_a] = true;
    }

    file.close();
    return slurped;
}

void traverse(size_t start, size_t end, int& counter)
{
    if (start == end) {
        counter++;
        return;
    }
    
    for (size_t i = 0; i < unique.size(); ++i) {
        if (connections[start][i] && !visited[i]) {
            if (islower(unique[i][0]))
                visited[i] = true;
            
            traverse(i, end, counter);
            visited[i] = false;
        }
    }
}

int main()
{
    int counter = 0;
    visited[find("start")] = true;
    traverse(find("start"), find("end"), counter);

    printf("%d\n", counter);
    return 0;
}
