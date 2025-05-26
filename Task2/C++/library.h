#pragma once

#include <algorithm> // For std::sort and std::shuffle
#include <chrono>	 // For std::chrono::steady_clock
#include <iomanip>	 // For std::setw, std::setfill
#include <iostream>
#include <random> // For std::mt19937 and std::shuffle
#include <string>
#include <vector>

// Global variables to store patient data and ticket pool
extern std::vector<std::string> global_patient_ticket_numbers;
extern std::vector<int> global_patient_durations;
extern std::vector<int> global_ticket_numbers_pool;
extern std::mt19937 global_rng;
extern int global_num_windows; // Needs to be global as functions can't take it as a member

// Function declarations
void initialize_queue_manager(int num_windows);
std::string generate_ticket_number();
std::string enqueue_patient(int duration);
void distribute_queue_to_windows();
