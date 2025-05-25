#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Перечисление для типов команд
enum class Type {
	CREATE_TRAIN,
	TRAINS_FOR_TOWN,
	TOWNS_FOR_TRAIN,
	TRAINS,
	CREATE_TRAM,
	TRAMS_IN_STOP,
	STOPS_IN_TRAM,
	TRAMS,
	CREATE_PLANE,
	PLANES_FOR_TOWN,
	TOWNS_FOR_PLANE,
	PLANES,
	CREATE_TRL,
	TRL_IN_STOP,
	STOPS_IN_TRL,
	TRLS
};

struct Tram {
	std::string name;
	std::vector<std::string> stops;
};

void processCommand(const std::string &command, const std::string &args, std::vector<Tram> &trams);
