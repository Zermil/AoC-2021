#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>

std::unordered_map<char, char> matches_opening = {
    { '(', ')' },
    { '[', ']' },
    { '{', '}' },
    { '<', '>' }
};

std::unordered_map<char, int> points = {
    { ')', 3	 },
    { ']', 57	 },
    { '}', 1197  },
    { '>', 25137 }
};

std::vector<std::string> slurp_input(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<std::string> parens;

    std::string line;
    while (std::getline(file, line)) {
	parens.emplace_back(line);
    }
    
    file.close();
    return parens;
}

char parse_input(const std::string& parens)
{
    std::stack<char> expected;
    
    for (const char& c : parens) {
	switch (c) {
	    case '(':
	    case '[':
	    case '{':
	    case '<': {
		expected.push(matches_opening[c]);
	    } break;

	    // Found closing bracket.
	    default: {
		if (expected.top() == c) {
		    expected.pop();
		} else return c;
	    }
	}
    }

    return '\0';
}

int main()
{
    std::vector<std::string> input = slurp_input("../input.txt");
    int answer = 0;
    
    for (const std::string& str : input) {
	char c = parse_input(str);
    
	if (c != '\0') {
	    answer += points[c];
	}
    }

    printf("%d\n", answer);
    return 0;
}
