#include "library.h"

int main() {
	initialize_warehouse();
	std::string command_line;
	while (true) {
		std::cout << "> ";
		std::getline(std::cin, command_line);
		if (command_line == "EXIT") {
			break;
		}
		process_command(command_line);
	}
	return 0;
}
