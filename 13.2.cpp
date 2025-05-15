#include <iostream>
#include <iomanip>
#include <vector>

void printPascalTriangle(int rows) {
    std::vector<std::vector<int>> triangle(rows);

    for (int i = 0; i < rows; ++i) {
        triangle[i].resize(i + 1);
        triangle[i][0] = triangle[i][i] = 1;

        for (int j = 1; j < i; ++j) {
            triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
        }
    }

    // Выравнивание
    int max_width = std::to_string(triangle[rows-1][rows/2]).length() + 1;

    for (int i = 0; i < rows; ++i) {
        std::cout << std::string((rows - i - 1) * max_width / 2, ' ');
        
        for (int j = 0; j <= i; ++j) {
            std::cout << std::setw(max_width) << triangle[i][j];
        }
        std::cout << std::endl;
    }
}

int main() {
    printPascalTriangle(10);
    return 0;
}