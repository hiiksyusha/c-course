#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <filesystem>

namespace fs = std::filesystem;

// Проверка на пробельную строку (с учетом всех видов пробелов)
bool is_whitespace_only(const std::string& str) {
    return std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::isspace(c);
    });
}

// Обработка файла с созданием резервной копии
bool process_file(const fs::path& filepath) {
    // Проверка существования файла
    if (!fs::exists(filepath)) {
        std::cerr << "Ошибка: файл не существует\n";
        return false;
    }

    // Создание резервной копии
    const auto backup_path = filepath.string() + ".bak";
    try {
        fs::copy_file(filepath, backup_path, fs::copy_options::overwrite_existing);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка при создании резервной копии: " << e.what() << '\n';
        return false;
    }

    // Открытие файлов
    std::ifstream input(filepath);
    if (!input) {
        std::cerr << "Ошибка: не удалось открыть файл для чтения\n";
        return false;
    }

    const auto temp_path = filepath.string() + ".tmp";
    std::ofstream output(temp_path);
    if (!output) {
        std::cerr << "Ошибка: не удалось создать временный файл\n";
        input.close();
        return false;
    }

    // Обработка содержимого
    std::string line;
    bool first_line = true;
    
    while (std::getline(input, line)) {
        if (!is_whitespace_only(line)) {
            if (!first_line) output << '\n';
            output << line;
            first_line = false;
        }
    }

    input.close();
    output.close();

    // Замена оригинального файла
    try {
        fs::remove(filepath);
        fs::rename(temp_path, filepath);
        std::cout << "Файл успешно обработан. Резервная копия сохранена как " << backup_path << '\n';
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка при замене файла: " << e.what() << '\n';
        return false;
    }
}

int main() {
    std::cout << "Очистка файла от пустых строк\n";
    std::cout << "Введите полный путь к файлу: ";
    
    std::string filename;
    std::getline(std::cin, filename);

    if (filename.empty()) {
        std::cerr << "Ошибка: не указано имя файла\n";
        return 1;
    }

    if (process_file(filename)) {
        std::cout << "Операция завершена успешно.\n";
        return 0;
    } else {
        std::cerr << "Операция завершена с ошибками.\n";
        return 1;
    }
}