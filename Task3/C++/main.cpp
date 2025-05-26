#include "library.h"

int main() {
	std::vector<Tram> trams;

	std::ifstream inputFile("data.conf");

	if (!inputFile.is_open()) {
		std::cerr << "Не удалось открыть файл" << std::endl;
		return 1;
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

		Type enumCommand;
		if (command == "CREATE_TRAM")
			enumCommand = Type::CREATE_TRAM;
		else if (command == "TRAMS_IN_STOP")
			enumCommand = Type::TRAMS_IN_STOP;
		else if (command == "STOPS_IN_TRAM")
			enumCommand = Type::STOPS_IN_TRAM;
		else if (command == "TRAMS")
			enumCommand = Type::TRAMS;
		processCommand(enumCommand, args, trams);
	}

	inputFile.close(); // Закрываем файл после использования

	return 0;
}
