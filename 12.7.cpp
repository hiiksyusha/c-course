#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>

namespace StringOperations {

template <typename Iterator>
class StringJoiner {
private:
    Iterator m_begin;
    Iterator m_end;
    std::string m_separator;

    static bool hasAlphabeticChars(const std::string& str) {
        for (char c : str) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                return true;
            }
        }
        return false;
    }

public:
    StringJoiner(Iterator begin, Iterator end, const std::string& sep)
        : m_begin(begin), m_end(end), m_separator(sep) {}

    std::string join() const {
        std::ostringstream result_stream;
        bool is_first_element = true;
        
        for (Iterator it = m_begin; it != m_end; ++it) {
            if (!is_first_element && hasAlphabeticChars(*it)) {
                result_stream << m_separator;
            }
            result_stream << *it;
            is_first_element = false;
        }
        
        return result_stream.str();
    }
};

template <typename Iterator>
std::string joinStrings(Iterator start, Iterator finish, const std::string& separator) {
    return StringJoiner<Iterator>(start, finish, separator).join();
}

} // namespace StringOperations

int main() {
    std::vector<std::string> words = {"hello", "123", "world", "456", "test"};
    std::string delimiter = "***";
    
    std::string combined = StringOperations::joinStrings(
        words.begin(), words.end(), delimiter);
    
    std::cout << "Joined result: " << combined << std::endl;
    
    return 0;
}