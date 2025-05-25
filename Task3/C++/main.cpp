#include "library.h"
#include <fstream> // Для работы с файлами

int main() {
	std::vector<Tram> trams; // Для варианта 2 (трамваи)

	// Открываем файл для чтения. Предполагаем, что файл называется "input.txt"
	// и находится в той же директории, что и исполняемый файл.
	std::ifstream inputFile("data.conf");

	// Проверяем, удалось ли открыть файл
	if (!inputFile.is_open()) {
		std::cerr << "Не удалось открыть файл input.txt" << std::endl;
		return 1; // Возвращаем код ошибки
	}

	std::string line;
	while (std::getline(inputFile, line)) { // Читаем файл построчно
		std::stringstream ss(line);
		std::string command;
		ss >> command;

		std::string args;
		std::getline(ss, args);				   // Считываем остаток строки как аргументы
		if (!args.empty() && args[0] == ' ') { // Убираем пробел в начале, если есть
			args = args.substr(1);
		}

		processCommand(command, args, trams);
	}

	inputFile.close(); // Закрываем файл после использования

	return 0;
}
