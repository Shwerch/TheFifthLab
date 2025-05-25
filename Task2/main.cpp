#include "library.h"

int main() {
	int num_windows;
	std::cout << ">>> Введите кол-во окон" << std::endl << ">>> ";
	std::cin >> num_windows;
	std::cin.ignore();

	QueueManager q_manager(num_windows);
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
				std::cout << ">>> " << q_manager.enqueue(duration) << std::endl;
			}
		} else if (line == "DISTRIBUTE") {
			q_manager.distribute_queue();
			break;
		}
	}

	return 0;
}
