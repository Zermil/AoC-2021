#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <string_view>

struct segment {
    std::string input[10];
    std::string output[4];
};

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
    
    for (const segment& seg : input) {
	for (size_t i = 0; i < 4; ++i) {
	    const size_t& len = seg.output[i].length();
	    
	    if (len == 2 || len == 4 || len == 3 || len == 7) {
		answer++;
	    }
	}
    }

    printf("%d\n", answer);
    return 0;
}
