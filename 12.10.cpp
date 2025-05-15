#include <iostream>
#include <vector>
#include <string>
#include <utility> // для std::pair

std::string longestPalindrome(const std::string& s) {
    if (s.empty()) return "";
    
    int n = s.size();
    int maxLength = 1;
    int start = 0;
    
    // Двумерный массив для кэширования результатов (i,j) = является ли подстрока палиндромом
    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
    
    // Все подстроки длины 1 являются палиндромами
    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }
    
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }
    
    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i < n - len + 1; ++i) {
            int j = i + len - 1; // Конечный индекс подстроки
            
            // Подстрока является палиндромом, если крайние символы совпадают
            // и внутренняя подстрока тоже палиндром (берем из кэша)
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                
                if (len > maxLength) {
                    start = i;
                    maxLength = len;
                }
            }
        }
    }
    
    return s.substr(start, maxLength);
}

int main() {
    std::string input;
    std::cout << "Введите строку для поиска палиндрома: ";
    std::getline(std::cin, input);
    
    std::string result = longestPalindrome(input);
    std::cout << "Самый длинный палиндром: " << result << std::endl;
    
    return 0;
}