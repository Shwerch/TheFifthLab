#include "library.h"

// Global variables definitions
std::vector<std::string> global_patient_ticket_numbers;
std::vector<int> global_patient_durations;
std::vector<int> global_ticket_numbers_pool;
std::mt19937 global_rng;
int global_num_windows;

void initialize_queue_manager(int num_windows) {
	global_num_windows = num_windows;
	global_rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());

	// Populate the pool with numbers from 100 to 999
	for (int i = 100; i <= 999; ++i) {
		global_ticket_numbers_pool.push_back(i);
	}
	// Shuffle the pool
	std::shuffle(global_ticket_numbers_pool.begin(), global_ticket_numbers_pool.end(), global_rng);
}

std::string generate_ticket_number() {
	if (global_ticket_numbers_pool.empty()) {
		return "TXXX"; // Or handle error appropriately
	}

	int num = global_ticket_numbers_pool.back();
	global_ticket_numbers_pool.pop_back();

	std::ostringstream oss;
	oss << "T" << std::setw(3) << std::setfill('0') << num;
	return oss.str();
}

std::string enqueue_patient(int duration) {
	std::string ticket = generate_ticket_number();
	global_patient_ticket_numbers.push_back(ticket);
	global_patient_durations.push_back(duration);
	return ticket;
}

void distribute_queue_to_windows() {
	// We need to sort patients based on their durations.
	// Since we can't use structs, we'll create a vector of indices and sort that
	// based on the durations in global_patient_durations.
	std::vector<int> sorted_indices(global_patient_durations.size());
	for (int i = 0; i < global_patient_durations.size(); ++i) {
		sorted_indices[i] = i;
	}

	// Sort indices based on durations in descending order
	std::sort(sorted_indices.begin(), sorted_indices.end(), [](int a_idx, int b_idx) {
		return global_patient_durations[a_idx] > global_patient_durations[b_idx];
	});

	// Keep track of the total duration for each window
	std::vector<int> window_total_durations(global_num_windows, 0);

	// Store assigned patient ticket numbers for each window
	std::vector<std::vector<std::string>> window_assignments_tickets(global_num_windows);
	// Store assigned patient durations for each window (optional, for printing total duration)
	// std::vector<std::vector<int>> window_assignments_durations(global_num_windows);

	for (int idx : sorted_indices) { // Iterate through sorted patient indices
		int min_duration = std::numeric_limits<int>::max();
		int min_duration_window_idx = -1;

		// Find the window with the minimum current total duration
		for (int i = 0; i < global_num_windows; ++i) {
			if (window_total_durations[i] < min_duration) {
				min_duration = window_total_durations[i];
				min_duration_window_idx = i;
			}
		}

		// Assign the patient to the window with the minimum duration
		if (min_duration_window_idx != -1) {
			window_assignments_tickets[min_duration_window_idx].push_back(
				global_patient_ticket_numbers[idx]);
			// window_assignments_durations[min_duration_window_idx].push_back(global_patient_durations[idx]);
			// // If needed for recalculation
			window_total_durations[min_duration_window_idx] += global_patient_durations[idx];
		}
	}

	// Print the distribution
	for (int i = 0; i < global_num_windows; ++i) {
		std::cout << ">>> Окно " << (i + 1) << " (" << window_total_durations[i] << " минут): ";
		bool first_patient = true;
		for (const std::string &ticket : window_assignments_tickets[i]) {
			if (!first_patient) {
				std::cout << ", ";
			}
			std::cout << ticket;
			first_patient = false;
		}
		std::cout << std::endl;
	}
}
