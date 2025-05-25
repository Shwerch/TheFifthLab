#include "library.h"

QueueManager::QueueManager(int num_windows)
	: num_windows_(num_windows), rng_(std::chrono::steady_clock::now().time_since_epoch().count()) {
	for (int i = 100; i <= 999; ++i) {
		ticket_numbers_pool_.push_back(i);
	}
	std::shuffle(ticket_numbers_pool_.begin(), ticket_numbers_pool_.end(), rng_);
}

std::string QueueManager::generate_ticket_number() {
	if (ticket_numbers_pool_.empty())
		throw "Kernel Panic";

	int num = ticket_numbers_pool_.back();
	ticket_numbers_pool_.pop_back();

	std::ostringstream oss;
	oss << "T" << std::setw(3) << std::setfill('0') << num;
	return oss.str();
}

std::string QueueManager::enqueue(int duration) {
	Patient p;
	p.ticket_number = generate_ticket_number();
	p.duration = duration;
	patients_.push_back(p);
	return p.ticket_number;
}

void QueueManager::distribute_queue() {
	std::sort(patients_.begin(), patients_.end(),
			  [](const Patient &a, const Patient &b) { return a.duration > b.duration; });

	std::vector<std::pair<int, int>> window_loads(num_windows_);
	for (int i = 0; i < num_windows_; ++i) {
		window_loads[i] = {0, i}; // {total_time, window_index}
	}

	std::vector<std::vector<Patient>> window_assignments(num_windows_);

	for (const auto &patient : patients_) {
		// Сортировка для нахождения минимально загруженного окна
		std::sort(window_loads.begin(), window_loads.end(),
				  [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
					  return a.first < b.first;
				  });

		int window_idx = window_loads[0].second;
		window_assignments[window_idx].push_back(patient);
		window_loads[0].first += patient.duration;
	}

	for (int i = 0; i < num_windows_; ++i) {
		int total_duration = 0;
		for (const auto &patient : window_assignments[i]) {
			total_duration += patient.duration;
		}
		std::cout << ">>> Окно " << (i + 1) << " (" << total_duration << " минут): ";
		bool first_patient = true;
		for (const auto &patient : window_assignments[i]) {
			if (!first_patient) {
				std::cout << ", ";
			}
			std::cout << patient.ticket_number;
			first_patient = false;
		}
		std::cout << std::endl;
	}
}
