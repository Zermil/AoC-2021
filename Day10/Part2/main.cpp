#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>

std::unordered_map<char, char> matches_opening = {
    { '(', ')' },
    { '[', ']' },
    { '{', '}' },
    { '<', '>' }
};

std::unordered_map<char, int> points = {
    { ')', 1 },
    { ']', 2 },
    { '}', 3 },
    { '>', 4 }
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

std::vector<char> match_parens(const std::string& parens)
{
    std::vector<char> output;
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
		}
	    }
	}
    }

    while (!expected.empty()) {
	output.emplace_back(expected.top());
	expected.pop();
    }
    
    return output;
}

int main()
{
    std::vector<std::string> input = slurp_input("../input.txt");
    std::vector<unsigned long long> scores;
    
    for (const std::string& str : input) {
        if (parse_input(str) != '\0') continue;

	std::vector<char> matches = match_parens(str);
	unsigned long long score = 0;
	
	for (const char& c : matches) {
	    score = (score * 5) + points[c];
	}

	scores.emplace_back(score);
    }

    std::sort(scores.begin(), scores.end());

    printf("%lld\n", scores[scores.size() / 2]);
    return 0;
}
