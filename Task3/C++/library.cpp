#include "library.h"

void processCommand(const Type command, const std::string &args, std::vector<Tram> &trams) {
	if (command == Type::CREATE_TRAM) {
		std::stringstream ss(args);
		std::string tramName;
		int numStops;
		ss >> tramName >> numStops;
		if (numStops < 2)
			return;
		for (Tram tram : trams) {
			if (tram.name == tramName)
				return;
		}
		Tram newTram;
		newTram.name = tramName;
		for (int i = 0; i < numStops; ++i) {
			std::string stop;
			ss >> stop;
			newTram.stops.push_back(stop);
		}
		if (newTram.stops.size() == 2) {
			if (newTram.stops.at(0) == newTram.stops.at(1))
				return;
		}
		trams.push_back(newTram);

	} else if (command == Type::TRAMS_IN_STOP) {
		std::string stopName = args;
		std::vector<std::string> tramsInThisStop;
		for (const auto &tram : trams) {
			for (const auto &stop : tram.stops) {
				if (stop == stopName) {
					tramsInThisStop.push_back(tram.name);
					break;
				}
			}
		}
		if (tramsInThisStop.empty()) {
			std::cout << "Trams is absent" << std::endl;
		} else {
			for (const auto &tramName : tramsInThisStop) {
				std::cout << tramName << std::endl;
			}
		}

	} else if (command == Type::STOPS_IN_TRAM) {
		std::string tramName = args;
		bool found = false;
		for (const auto &tram : trams) {
			if (tram.name == tramName) {
				found = true;
				std::map<std::string, std::vector<std::string>> stopsAndTrams;
				for (const auto &stop : tram.stops) {
					for (const auto &otherTram : trams) {
						if (otherTram.name != tramName) { // Исключаем текущий трамвай
							for (const auto &otherStop : otherTram.stops) {
								if (otherStop == stop) {
									stopsAndTrams[stop].push_back(otherTram.name);
								}
							}
						}
					}
				}
				for (const auto &stop : tram.stops) {
					std::cout << "Stop " << stop << ": ";
					if (stopsAndTrams.count(stop) && !stopsAndTrams[stop].empty()) {
						for (size_t i = 0; i < stopsAndTrams[stop].size(); ++i) {
							std::cout << stopsAndTrams[stop][i];
							if (i < stopsAndTrams[stop].size() - 1) {
								std::cout << " ";
							}
						}
						std::cout << std::endl;
					} else {
						std::cout << "0" << std::endl;
					}
				}
				break;
			}
		}
		if (!found) {
			std::cout << "Trams is absent" << std::endl;
		}

	} else if (command == Type::TRAMS) {
		if (trams.empty()) {
			std::cout << "Trams is absent" << std::endl;
		} else {
			for (const auto &tram : trams) {
				std::cout << "TRAM " << tram.name << ":";
				for (const auto &stop : tram.stops) {
					std::cout << " " << stop;
				}
				std::cout << std::endl;
			}
		}
	}
}
