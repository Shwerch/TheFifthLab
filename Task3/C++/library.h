#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Перечисление для типов команд
enum class Type { CREATE_TRAM, TRAMS_IN_STOP, STOPS_IN_TRAM, TRAMS };

struct Tram {
	std::string name;
	std::vector<std::string> stops;
};

void processCommand(const Type command, const std::string &args, std::vector<Tram> &trams);
