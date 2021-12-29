#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <algorithm>

constexpr size_t alpha_sz = 26;
size_t pair_count[alpha_sz][alpha_sz];
size_t freq[alpha_sz];

std::string poly_start;
std::unordered_map<std::string, char> map;

void slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    
    std::getline(file, line);
    poly_start = line;
    
    std::getline(file, line); // skip empty line;
    for (const char& c : poly_start) {
        freq[c - 'A'] += 1;
    }

    for (size_t i = 0; i < poly_start.length() - 1; ++i) {
        size_t a = poly_start[i + 0] - 'A';
        size_t b = poly_start[i + 1] - 'A';
        
        pair_count[a][b]++;
    }
    
    while (getline(file, line)) {
        map[line.substr(0, 2)] = line[line.length() - 1];
    }
    
    file.close();
}

void process_polymer()
{
    size_t new_pair_count[alpha_sz][alpha_sz] = {};
    
    for (size_t row = 0; row < alpha_sz; ++row) {
        for (size_t col = 0; col < alpha_sz; ++col) {            
            std::string pair = std::string(1, (char)(row + 'A')) + (char)(col + 'A');
            char c = map[pair];
            
            new_pair_count[row][c - 'A'] += pair_count[row][col];
            new_pair_count[c - 'A'][col] += pair_count[row][col];
            
            freq[c - 'A'] += pair_count[row][col];
        }
    }

    memcpy(pair_count, new_pair_count, sizeof(new_pair_count));
}

int main()
{
    slurp_input("../input.txt");

    for (int i = 0; i < 10; ++i) {
        process_polymer();
    }

    std::sort(freq, freq + alpha_sz, [](size_t a, size_t b) { return a > b; });
    
    size_t least_common;
    for (size_t i = alpha_sz - 1; i >= 0; --i) {
        if (freq[i] > 0) {
            least_common = freq[i];
            break;
        }
    }
    
    printf("%lld\n", freq[0] - least_common);
    return 0;
}
