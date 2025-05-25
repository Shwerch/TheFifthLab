#pragma once

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random> // For std::mt19937 and std::shuffle
#include <string>
#include <vector>

struct Patient {
	std::string ticket_number;
	int duration;
};

class QueueManager {
  public:
	QueueManager(int num_windows);
	std::string enqueue(int duration);
	void distribute_queue();

  private:
	int num_windows_;
	std::vector<Patient> patients_;
	std::vector<int> ticket_numbers_pool_;
	std::mt19937 rng_;

	std::string generate_ticket_number();
};
