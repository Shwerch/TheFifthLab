#pragma once

#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Cell {
	std::string item_name;
	int quantity;
	int max_capacity = 10;
	bool is_empty() const { return quantity == 0; }
};

extern std::map<char, std::vector<std::vector<std::vector<Cell>>>> warehouse;

void initialize_warehouse();
void process_command(const std::string &command_line);
void add_item(const std::string &item_name, int quantity, const std::string &address);
void remove_item(const std::string &item_name, int quantity, const std::string &address);
void display_info();
Cell *get_cell_from_address(const std::string &address);
std::string get_address_from_indices(char zone_char, int rack_idx, int section_idx, int shelf_idx);
