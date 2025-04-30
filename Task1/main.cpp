#include "library.h"

using namespace std;

// Зона хранения - стеллажи
map<char, set<int>> zones = {{'A', {}}};
// Стеллаж - вертикальные секции
map<int, set<int>> racks = {};
// Вертикальная секция - номера полок
map<int, set<int>> sections = {};
// Полка - информация о товаре: ID и количество
map<int, pair<int, int>> shelfs = {};
// Название товара - ID товара
map<string, int> productIDs = {};

// Щас можно вставить полки 987 17 616 26 266 и их будет 5, а надо по порядку 1 2 3 4 5
bool add(int productID, int count, char zone, int rack, int section, int shelf) {
	zones.at('A').insert(rack); // В зоне A есть стеллаж под номером rack
	if (zones.at('A').size() > RACKS)
		return false;
	racks.at(rack).insert(section); // В стеллаже rack есть секция под номером section
	if (racks.at(rack).size() > SECTIONS)
		return false;
	sections.at(section).insert(shelf); // В секции section есть полка под номером shelf
	if (racks.at(rack).size() > SECTIONS)
		return false;
	pair<int, int> myPair = {1, 2};
	shelfs.at(shelf).swap(myPair);
	return true;
}

int main() { return 0; }
