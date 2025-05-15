#include <iostream>
#include <vector>
#include <cctype>
#include <unordered_map>

using namespace std;

class TextProcessor {
private:
    unordered_map<char, bool> delimiter_map;

    void initializeDelimiters() {
        const vector<char> delims = {
            ' ', '\n', '\t', ';', '.', ',', '!', '?', ':', '-',
            '/', '\\', '(', ')', '[', ']', '{', '}', '<', '>',
            '@', '#', '$', '%', '^', '&', '*', '~', '`', '+',
            '=', '|', '"', '\''
        };
        for (char d : delims) {
            delimiter_map[d] = true;
        }
    }

public:
    TextProcessor() {
        initializeDelimiters();
    }

    bool isDelimiter(char c) const {
        return delimiter_map.find(c) != delimiter_map.end();
    }

    string formatText(const string& input) const {
        string output;
        bool capitalizeNext = true;

        for (char current : input) {
            if (isDelimiter(current)) {
                output += current;
                capitalizeNext = true;
            } else {
                output += capitalizeNext ? toupper(current) : tolower(current);
                capitalizeNext = false;
            }
        }

        return output;
    }
};

int executeProgram() {
    const string sampleText = "heLLo";

    TextProcessor processor;
    string processed = processor.formatText(sampleText);

    cout << "Original:\n" << sampleText << "\n\n";
    cout << "Processed:\n" << processed << endl;

    return 0;
}

int main() {
    return executeProgram();
}