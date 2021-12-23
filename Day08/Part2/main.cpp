#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <string_view>
#include <algorithm>
#include <unordered_map>

std::unordered_map<int, int> display = {
    { 0b1110111, 0 },
    { 0b0100100, 1 },
    { 0b1011101, 2 },
    { 0b1101101, 3 },
    { 0b0101110, 4 },
    { 0b1101011, 5 },
    { 0b1111011, 6 },
    { 0b0100101, 7 },
    { 0b1111111, 8 },
    { 0b1101111, 9 } 
};

std::unordered_map<char, int> connections = {
    { 'a', 0b0000000 },
    { 'b', 0b0000000 },
    { 'c', 0b0000000 },
    { 'd', 0b0000000 },
    { 'e', 0b0000000 },
    { 'f', 0b0000000 },
    { 'g', 0b0000000 }
};

struct segment {
    std::string input[10];
    std::string output[4];
};

inline void set_connections(const std::string& wiring)
{
    connections[wiring[0]] = 0b0000001;
    connections[wiring[1]] = 0b0000010;
    connections[wiring[2]] = 0b0000100;
    connections[wiring[3]] = 0b0001000;
    connections[wiring[4]] = 0b0010000;
    connections[wiring[5]] = 0b0100000;
    connections[wiring[6]] = 0b1000000;
}

bool check_pattern(const segment& seg)
{       
    for (size_t i = 0; i < 10; ++i) {
	int pattern = 0b0000000;
	for (const char& c : seg.input[i]) {
	    pattern |= connections[c];
	}

	if (display.find(pattern) == display.end()) {
	    return false;
	}
    }

    return true;
}

void assign_pattern(const std::vector<std::string>& all_permutations, const segment& seg)
{
    /* Note(Aiden): Realistically it will 100% find the matching pattern
       since it's going through all possible permutations,
       this function could also return "connections" (above)
    */
    for (const std::string& wiring : all_permutations) {
	set_connections(wiring);
	
	if (check_pattern(seg)) {
	    return;
	}
    }
}

/* Note(Aiden): You could probably figure out some smart
   and clever way to identify intersections and mask
   with bit operations to identify digits and narrow everything down.
   Source: https://www.nayuki.io/res/next-lexicographical-permutation-algorithm/nextperm.hpp
*/
bool lex_perm(std::string& str)
{
    if (str.length() == 0)
	return false;

    size_t i = str.length() - 1;
    while (i > 0 && str[i - 1] >= str[i]) {
	i--;
    }

    if (i == 0)
	return false;

    size_t j = str.length() - 1;
    while (str[j] <= str[i - 1]) {
	j--;
    }
    
    std::swap(str[i - 1], str[j]);
    std::reverse(str.begin() + i, str.end());
    
    return true;
}

void populate_segments_input(std::string_view view, segment& seg)
{
    size_t pos = 0;
    size_t index = 0;
    
    for (size_t i = 0; i < view.length(); ++i) {
	const char& c = view[i];
      
	if (c == ' ') {
	    seg.input[index++] = view.substr(pos, i - pos);
	    pos = i + 1;
	}
    }

    // EOF
    seg.input[index] = view.substr(view.find_last_of(' ') + 1);
}

void populate_segments_output(std::string_view view, segment& seg)
{
    size_t pos = 0;
    size_t index = 0;
    
    for (size_t i = 0; i < view.length(); ++i) {
	const char& c = view[i];
      
	if (c == ' ') {
	    seg.output[index++] = view.substr(pos, i - pos);
	    pos = i + 1;
	}
    }

    // EOF
    seg.output[index] = view.substr(view.find_last_of(' ') + 1);
}

std::vector<segment> slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<segment> segments;

    segment seg = {};
    std::string line;
    
    while (std::getline(file, line)) {
	std::string_view view = std::string_view(line);

	auto delimiter_pos = view.find_first_of('|');
	std::string_view input_side = view.substr(0, delimiter_pos - 1);
	std::string_view output_side = view.substr(delimiter_pos + 2);

	populate_segments_input(input_side, seg);
	populate_segments_output(output_side, seg);
      
	segments.emplace_back(seg);
    }
	
    file.close();
    return segments;
}

int main()
{
    std::vector<segment> input = slurp_input("../input.txt");
    int answer = 0;
    
    // Prepare permutations.
    std::string to_perm = "abcdefg";
    
    std::vector<std::string> all_permutations;
    all_permutations.emplace_back(to_perm);
    
    while (lex_perm(to_perm)) {
	all_permutations.emplace_back(to_perm);
    }
    
    for (const segment& seg : input) {
	assign_pattern(all_permutations, seg);
	
	int out_num = 0;
	for (size_t i = 0; i < 4; ++i) {
	    int digit = 0b0000000;
	    
	    for (const char& c : seg.output[i]) {
		digit |= connections[c];
	    }

	    out_num = (out_num * 10) + display[digit];
	}

	answer += out_num;
    }
    
    printf("%d\n", answer);
    return 0;
}
