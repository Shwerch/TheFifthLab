#include "library.h"
#include <cstdio>

// Глобальный счетчик для ID студентов
static int next_student_id = 1;

void process_command(const std::string &command_line, std::vector<Student> &students,
					 std::vector<int> &top_list) {
	std::stringstream ss(command_line);
	std::string command_type;
	ss >> command_type;

	if (command_type == "NEW_STUDENTS") {
		int count;
		ss >> count;
		new_students(count, students, top_list); // Передаем top_list
	} else if (command_type == "SUSPICIOUS") {
		int student_id;
		ss >> student_id;
		suspicious_student(student_id, students, top_list);
	} else if (command_type == "IMMORTAL") {
		int student_id;
		ss >> student_id;
		immortal_student(student_id, students, top_list);
	} else if (command_type == "TOP-LIST") {
		top_list_output(students, top_list);
	} else if (command_type == "SCOUNT") {
		scount_output(students, top_list);
	} else {
		// Неизвестная команда, можно добавить обработку ошибки
	}
}

void new_students(int count, std::vector<Student> &students, std::vector<int> &top_list) {
	if (count > 0) {
		std::cout << "Welcome " << count << " clever students!" << std::endl;
		for (int i = 0; i < count; ++i) {
			students.emplace_back(
				next_student_id++); // Создаем нового студента и добавляем в вектор
		}
	} else {
		int students_to_remove = std::min(std::abs(count), static_cast<int>(top_list.size()));

		std::cout << "GoodBye " << students_to_remove << " clever students!" << std::endl;

		for (int i = 0; i < students_to_remove; ++i) {
			if (!students.empty()) {
				int removed_student_id = top_list.back(); // ID удаляемого студента
				top_list.pop_back();					  // Удаляем последнего студента

				// Удаляем студента из top_list, если он там был
				std::erase_if(students, [removed_student_id](const Student &s) {
					return s.id == removed_student_id;
				});
			} else {
				break;
			}
		}
	}
}

void suspicious_student(int student_id, std::vector<Student> &students,
						std::vector<int> &top_list) {
	for (Student &s : students) {
		if (s.id == student_id) {
			if (std::find(top_list.begin(), top_list.end(), s.id) == top_list.end() &&
				!s.immortal) {
				top_list.push_back(s.id);
				s.suspected = true;
				std::cout << "The suspected student " << student_id << std::endl;
				break;
			}
		}
	}
}

void immortal_student(int student_id, std::vector<Student> &students, std::vector<int> &top_list) {
	for (Student &s : students) {
		if (s.id == student_id) {
			s.immortal = true;
			s.suspected = false;
			top_list.erase(std::remove(top_list.begin(), top_list.end(), s.id), top_list.end());
			std::cout << "Student " << student_id << " is immortal!" << std::endl;
			break;
		}
	}
}

void top_list_output(const std::vector<Student> &students, const std::vector<int> &top_list) {
	// Создаем копию для сортировки
	std::vector<int> sorted_top_list = top_list;
	std::sort(sorted_top_list.begin(), sorted_top_list.end()); // Сортируем по ID

	std::cout << "List of students for expulsion: ";
	if (sorted_top_list.empty()) {
		std::cout << "" << std::endl; // Пустая строка, если список пуст
	} else {
		for (size_t i = 0; i < sorted_top_list.size(); ++i) {
			std::cout << "Student " << sorted_top_list[i];
			if (i < sorted_top_list.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
	}
}

void scount_output(const std::vector<Student> &students, const std::vector<int> &top_list) {
	std::cout << "List of students for expulsion consists of " << top_list.size() << " students"
			  << std::endl;
}
