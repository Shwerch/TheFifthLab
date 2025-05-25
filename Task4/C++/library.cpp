#include "library.h"
#include <algorithm> // Для std::sort и std::remove
#include <iostream>
#include <sstream> // Для std::stringstream

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
		new_students(count, students);
	} else if (command_type == "SUSPICIOUS") {
		int student_id;
		ss >> student_id;
		suspicious_student(student_id, students, top_list);
	} else if (command_type == "IMMORTIAL") {
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

void new_students(int count, std::vector<Student> &students) {
	if (count > 0) {
		std::cout << "Welcome " << count << " clever students!" << std::endl;
		for (int i = 0; i < count; ++i) {
			students.emplace_back(
				next_student_id++); // Создаем нового студента и добавляем в вектор
		}
	} else {
		std::cout << "GoodBye " << std::abs(count) << " clever students!" << std::endl;
		// По условию задачи, отрицательное count означает только вывод сообщения.
		// Если бы требовалось удаление, то нужно было бы учесть логику удаления из общего списка
		// студентов.
	}
}

void suspicious_student(int student_id, std::vector<Student> &students,
						std::vector<int> &top_list) {
	bool found = false;
	for (Student &s : students) {
		if (s.id == student_id) {
			s.suspected = true;
			// Добавляем студента в top_list, если его там еще нет и он не бессмертен
			// Если студент бессмертен, он не должен попадать в top_list.
			if (std::find(top_list.begin(), top_list.end(), s.id) == top_list.end() &&
				!s.immortal) {
				top_list.push_back(s.id);
			}
			std::cout << "The suspected student " << student_id << std::endl;
			found = true;
			break;
		}
	}
	// Если студент не найден, по примеру ничего не выводим.
}

void immortal_student(int student_id, std::vector<Student> &students, std::vector<int> &top_list) {
	bool found = false;
	for (Student &s : students) {
		if (s.id == student_id) {
			s.immortal = true;
			// Удаляем студента из top_list, если он там был (даже если он был добавлен ранее)
			// erase-remove idiom для эффективного удаления
			top_list.erase(std::remove(top_list.begin(), top_list.end(), s.id), top_list.end());
			std::cout << "Student " << student_id << " is immortal!" << std::endl;
			found = true;
			break;
		}
	}
	// Если студент не найден, по примеру ничего не выводим.
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
