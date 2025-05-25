#include <iostream>
#include <fstream>
#include <string>
#include "library.h"

int main() {
    std::ifstream inputFile("data.conf");
    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл data.conf" << std::endl;
        return 1;
    }

    int num_commands;
    inputFile >> num_commands;
    inputFile.ignore(); // Игнорируем остаток строки после числа команд

    std::vector<Student> students; // Все студенты
    std::vector<int> top_list;     // Индексы студентов в списке на отчисление

    std::string line;
    for (int i = 0; i < num_commands; ++i) {
        std::getline(inputFile, line);
        process_command(line, students, top_list);
    }

    inputFile.close();
    return 0;
}
