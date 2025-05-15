#include <iostream>
#include <string>
#include <vector>

std::string compressRLE(const std::string& input) {
    if (input.empty()) return "";

    std::string compressed;
    int count = 1;
    char current = input[0];

    for (size_t i = 1; i < input.size(); ++i) {
        if (input[i] == current) {
            count++;
        } else {
            compressed += current;
            if (count > 1) {
                compressed += std::to_string(count);
            }
            current = input[i];
            count = 1;
        }
    }

    // Добавляем последний символ и его счетчик
    compressed += current;
    if (count > 1) {
        compressed += std::to_string(count);
    }

    return compressed;
}

int main() {
    // Тестовые данные
    const std::vector<std::string> test_cases = {
        "AAABBBCCCD", 
        "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWB"
    };

    // Тестирование функции сжатия
    for (const auto& original : test_cases) {
        std::string compressed = compressRLE(original);
        
        std::cout << "Original:   " << original << "\n";
        std::cout << "Compressed: " << compressed << "\n";
    }

    return 0;
}