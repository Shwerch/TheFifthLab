#include "library.h"

std::map<std::array<int, 4>, std::pair<int, int>> storage;
std::map<int, std::string> productNames;

AddProduct add(int productID, int count, int zone, int rack, int section, int shelf) {
	if (!LIMIT(1, zone, ZONEZ) || !LIMIT(1, rack, RACKS) || !LIMIT(1, section, SECTIONS) ||
		!LIMIT(1, shelf, SHELFS) || !LIMIT(1, count, 10) ||
		productNames.find(productID) == productNames.end())
		return AddProduct::INCORRECT_INPUT_DATA;
	std::array<int, 4> array = {static_cast<int>(zone), rack, section, shelf};
	for (std::pair<std::array<int, 4>, std::pair<int, int>> element : storage) {
		if (element.first != array)
			continue;
		else if (element.second.first != productID)
			return AddProduct::CELL_IS_OCCUPIED_BY_ANOTHER_PRODUCT;
		else if (element.second.second + count > 10)
			return AddProduct::NOT_ENOUGH_SPACE_IN_THE_CELL;
		element.second.second += count;
		return AddProduct::ADDED_EXISTED_PROSUCT_SUCCESS;
	}
	std::pair<int, int> pair = {productID, count};
	storage.insert({array, pair});
	return AddProduct::ADDED_NEW_PROSUCT_SUCCESS;
}

RemoveProduct remove(int productID, int count, int zone, int rack, int section, int shelf) {
	if (!LIMIT(1, zone, ZONEZ) || !LIMIT(1, rack, RACKS) || !LIMIT(1, section, SECTIONS) ||
		!LIMIT(1, shelf, SHELFS) || !LIMIT(1, count, 10) ||
		productNames.find(productID) == productNames.end())
		return RemoveProduct::INCORRECT_INPUT_DATA;
	std::array<int, 4> array = {zone, rack, section, shelf};
	for (std::pair<std::array<int, 4>, std::pair<int, int>> element : storage) {
		if (element.first != array)
			continue;
		else if (element.second.first != productID)
			return RemoveProduct::CELL_IS_OCCUPIED_BY_ANOTHER_PRODUCT;
		element.second.second -= count;
		if (element.second.second <= 0) {
			storage.erase(array);
			return RemoveProduct::COMPLETE_REMOVAL_PRODUCT_SUCCESS;
		}
		return RemoveProduct::REMOVAL_PRODUCT_SUCCESS;
	}
	return RemoveProduct::NOT_FOUND_PRODUCT;
}

void info() {
	for (int zone = 1; zone <= ZONEZ; zone++) {
		for (int rack = 1; rack < RACKS; rack++) {
			for (int section = 1; section < SECTIONS; section++) {
				for (int shelf = 1; shelf < SHELFS; shelf++) {
					std::cout << static_cast<char>(zone + static_cast<int>('A') - 1) << rack
							  << section;
				}
			}
		}
	}
}

int main() { return 0; }
