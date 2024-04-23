#pragma once
#include <sstream>
#include <string>
#include <vector>

using std::string, std::vector, std::getline;

class StringUtils {
public:
    static vector<string> split(const string& s, const char& delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);

        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }

        return tokens;
    }
};
