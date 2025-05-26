#include "library.h"

int main() {
	int num_windows;
	std::cout << ">>> Введите кол-во окон" << std::endl;
	std::cin >> num_windows;
	std::cin.ignore(); // Consume the newline character

	initialize_queue_manager(num_windows); // Initialize global variables

	std::string line;

	while (true) {
		std::cout << "<<< ";
		std::getline(std::cin, line);

		if (line.rfind("ENQUEUE", 0) == 0) {
			size_t space_pos = line.find(' ');
			if (space_pos != std::string::npos) {
				int duration = std::stoi(line.substr(space_pos + 1));
				if (duration < 1)
					continue;
				std::cout << ">>> " << enqueue_patient(duration) << std::endl;
			}
		} else if (line == "DISTRIBUTE") {
			distribute_queue_to_windows();
			break;
		} else {
			// For this problem, we assume input is always ENQUEUE or DISTRIBUTE
		}
	}

	return 0;
}
