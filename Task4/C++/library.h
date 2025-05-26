#pragma once

#include <algorithm> // Для std::sort и std::remove
#include <fstream>
#include <iostream>
#include <sstream> // Для std::stringstream
#include <string>
#include <vector>

// Структура для представления студента
struct Student {
	int id;
	bool suspected;
	bool immortal;

	// Конструктор по умолчанию
	Student() : id(0), suspected(false), immortal(false) {}

	// Конструктор с инициализацией id
	Student(int student_id) : id(student_id), suspected(false), immortal(false) {}
};

// Прототип функции для обработки команд
void process_command(const std::string &command_line, std::vector<Student> &students,
					 std::vector<int> &top_list);

// Вспомогательные функции (прототипы)
void new_students(int count, std::vector<Student> &students,
				  std::vector<int> &top_list); // Добавил top_list для обработки удаления
void suspicious_student(int student_id, std::vector<Student> &students, std::vector<int> &top_list);
void immortal_student(int student_id, std::vector<Student> &students, std::vector<int> &top_list);
void top_list_output(const std::vector<Student> &students, const std::vector<int> &top_list);
void scount_output(const std::vector<Student> &students, const std::vector<int> &top_list);
