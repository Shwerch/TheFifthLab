#include "library.h"

std::map<char, std::vector<std::vector<std::vector<Cell>>>> warehouse;

void initialize_warehouse() {
	// Только зона'A'
	char zone_char = 'A';
	warehouse[zone_char].resize(10); // 10 стеллажей
	for (auto &rack : warehouse[zone_char]) {
		rack.resize(7); // 7 вертикальных секций
		for (auto &section : rack) {
			section.resize(4); // 4 полки
			for (auto &cell : section) {
				cell.item_name = "";
				cell.quantity = 0;
			}
		}
	}
}

Cell *get_cell_from_address(const std::string &address) {
	if (address.length() < 4) {
		return nullptr; // Несуществующий адрес
	}

	char zone_char = address[0];
	if (zone_char != 'A') {
		return nullptr; // Несуществующая зона
	}

	try {
		int rack_num = std::stoi(address.substr(1, address.length() - 3));
		int section_num = std::stoi(address.substr(address.length() - 2, 1));
		int shelf_num = std::stoi(address.substr(address.length() - 1, 1));

		if (rack_num < 1 || rack_num > 10 || section_num < 1 || section_num > 7 || shelf_num < 1 ||
			shelf_num > 4) {
			return nullptr; // Вышел за пределы
		}

		// Adjust to 0-based indexing
		return &warehouse[zone_char][rack_num - 1][section_num - 1][shelf_num - 1];

	} catch (const std::invalid_argument &e) {
		return nullptr; // Ошибка конвертации
	} catch (const std::out_of_range &e) {
		return nullptr; // Выход за предел stoi
	}
}

std::string get_address_from_indices(char zone_char, int rack_idx, int section_idx, int shelf_idx) {
	std::stringstream ss;
	ss << zone_char << (rack_idx + 1) << (section_idx + 1) << (shelf_idx + 1);
	return ss.str();
}

void add_item(const std::string &item_name, int quantity, const std::string &address) {
	Cell *cell = get_cell_from_address(address);
	if (!cell) {
		std::cout << "Error: Invalid address '" << address << "'.\n";
		return;
	} else if (quantity < 1) {
		std::cout << "Error: Invalid quantity '" << quantity << "'.\n";
		return;
	}

	if (cell->is_empty()) {
		if (quantity > cell->max_capacity) {
			std::cout << "Error: Cannot add " << quantity << " units. Cell capacity is "
					  << cell->max_capacity << ".\n";
			return;
		}
		cell->item_name = item_name;
		cell->quantity = quantity;
		std::cout << "Added " << quantity << " " << item_name << " to " << address << ".\n";
	} else if (cell->item_name != item_name) {
		std::cout << "Error: Cell " << address << " already contains '" << cell->item_name
				  << "'. Cannot add '" << item_name << "'.\n";
	} else {
		if (cell->quantity + quantity > cell->max_capacity) {
			std::cout << "Error: Adding " << quantity << " units would exceed cell capacity ("
					  << cell->max_capacity << "). Current: " << cell->quantity << ".\n";
			return;
		}
		cell->quantity += quantity;
		std::cout << "Added " << quantity << " " << item_name << " to " << address
				  << ". Total: " << cell->quantity << ".\n";
	}
}

void remove_item(const std::string &item_name, int quantity, const std::string &address) {
	Cell *cell = get_cell_from_address(address);
	if (!cell) {
		std::cout << "Error: Invalid address '" << address << "'.\n";
		return;
	}

	if (cell->is_empty() || cell->item_name != item_name) {
		std::cout << "Error: Cell " << address << " does not contain '" << item_name << "'.\n";
		return;
	}

	if (cell->quantity < quantity) {
		std::cout << "Error: Insufficient quantity of '" << item_name << "' in cell " << address
				  << ". Available: " << cell->quantity << ".\n";
		return;
	}

	cell->quantity -= quantity;
	std::cout << "Removed " << quantity << " " << item_name << " from " << address << ".\n";
	if (cell->quantity == 0) {
		cell->item_name = "";
		std::cout << "Cell " << address << " is now empty.\n";
	}
}

void display_info() {
	int total_capacity = 0;
	int total_occupied = 0;

	char zone_char = 'A';

	int zone_capacity = 0;
	int zone_occupied = 0;

	// Вычислить проценты занятости
	for (const auto &rack : warehouse[zone_char]) {
		for (const auto &section : rack) {
			for (const auto &cell : section) {
				total_capacity += cell.max_capacity;
				zone_capacity += cell.max_capacity;
				if (!cell.is_empty()) {
					total_occupied += cell.quantity;
					zone_occupied += cell.quantity;
				}
			}
		}
	}

	// Общий процент загрузки склада
	double warehouse_load_percent =
		(total_capacity == 0) ? 0 : (static_cast<double>(total_occupied) / total_capacity) * 100;
	std::cout << "\n--- Warehouse Information ---\n";
	std::cout << "Warehouse Loading: " << std::fixed << std::setprecision(2)
			  << warehouse_load_percent << "%\n";

	// Zone loading percentage for 'A'
	double zone_load_percent =
		(zone_capacity == 0) ? 0 : (static_cast<double>(zone_occupied) / zone_capacity) * 100;
	std::cout << "Zone " << zone_char << " Loading: " << std::fixed << std::setprecision(2)
			  << zone_load_percent << "%\n";

	std::cout << "\n--- Occupied Cells ---\n";
	for (int rack_idx = 0; rack_idx < warehouse[zone_char].size(); ++rack_idx) {
		for (int section_idx = 0; section_idx < warehouse[zone_char][rack_idx].size();
			 ++section_idx) {
			for (int shelf_idx = 0; shelf_idx < warehouse[zone_char][rack_idx][section_idx].size();
				 ++shelf_idx) {
				const Cell &cell = warehouse[zone_char][rack_idx][section_idx][shelf_idx];
				if (!cell.is_empty()) {
					std::cout << get_address_from_indices(zone_char, rack_idx, section_idx,
														  shelf_idx)
							  << ": " << cell.item_name << " (" << cell.quantity << " units)\n";
				}
			}
		}
	}

	std::cout << "\n--- Empty Cells ---\n";
	std::cout << "Zone " << zone_char << ":\n";
	for (int rack_idx = 0; rack_idx < 10; ++rack_idx) {
		for (int shelf_idx = 0; shelf_idx < 4; ++shelf_idx) {
			for (int section_idx = 0; section_idx < 7; ++section_idx) {
				const Cell &cell = warehouse[zone_char][rack_idx][section_idx][shelf_idx];
				if (cell.is_empty()) {
					std::cout << std::setw(8)
							  << get_address_from_indices(zone_char, rack_idx, section_idx,
														  shelf_idx);
				} else {
					std::cout << std::setw(8) << ""; // Вывести пустое место если полка пустая
				}
			}
			std::cout << "\n";
		}
	}
	std::cout << "----------------------------\n";
}

void process_command(const std::string &command_line) {
	std::stringstream ss(command_line);
	std::string command;
	ss >> command;

	if (command == "ADD") {
		std::string item_name;
		int quantity;
		std::string address;
		ss >> item_name >> quantity >> address;
		add_item(item_name, quantity, address);
	} else if (command == "REMOVE") {
		std::string item_name;
		int quantity;
		std::string address;
		ss >> item_name >> quantity >> address;
		remove_item(item_name, quantity, address);
	} else if (command == "INFO") {
		display_info();
	} else {
		std::cout << "Unknown command: " << command << "\n";
	}
}
