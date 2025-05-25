import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Library {

	private static int nextStudentId = 1;

	public static void processCommand(
		String commandLine,
		List<Student> students,
		List<Integer> topList
	) {
		String[] parts = commandLine.split(" ");
		String commandType = parts[0];

		switch (commandType) {
			case "NEW_STUDENTS":
				int count = Integer.parseInt(parts[1]);
				newStudents(count, students);
				break;
			case "SUSPICIOUS":
				int studentIdSus = Integer.parseInt(parts[1]);
				suspiciousStudent(studentIdSus, students, topList);
				break;
			case "IMMORTIAL":
				int studentIdImm = Integer.parseInt(parts[1]);
				immortalStudent(studentIdImm, students, topList);
				break;
			case "TOP-LIST":
				topListOutput(students, topList);
				break;
			case "SCOUNT":
				scountOutput(students, topList);
				break;
			default:
				// Неизвестная команда, можно добавить обработку ошибки
				break;
		}
	}

	private static void newStudents(int count, List<Student> students) {
		if (count > 0) {
			System.out.println("Welcome " + count + " clever students!");
			for (int i = 0; i < count; i++) {
				students.add(new Student(nextStudentId++));
			}
		} else {
			System.out.println(
				"GoodBye " + Math.abs(count) + " clever students!"
			);
		}
	}

	private static void suspiciousStudent(
		int studentId,
		List<Student> students,
		List<Integer> topList
	) {
		for (Student s : students) {
			if (s.id == studentId) {
				s.suspected = true;
				if (!topList.contains(s.id) && !s.immortal) {
					topList.add(s.id);
				}
				System.out.println("The suspected student " + studentId);
				break;
			}
		}
		// По условию задачи, ничего не выводим, если студент не найден.
	}

	private static void immortalStudent(
		int studentId,
		List<Student> students,
		List<Integer> topList
	) {
		for (Student s : students) {
			if (s.id == studentId) {
				s.immortal = true;
				// Удаляем студента из topList, если он там был
				topList.remove(Integer.valueOf(s.id)); // Удаляем по значению объекта Integer
				System.out.println("Student " + studentId + " is immortal!");
				break;
			}
		}
		// По условию задачи, ничего не выводим, если студент не найден.
	}

	private static void topListOutput(
		List<Student> students,
		List<Integer> topList
	) {
		// Создаем копию для сортировки и сортируем
		List<Integer> sortedTopList = new ArrayList<>(topList);
		Collections.sort(sortedTopList); // Сортируем по ID

		System.out.print("List of students for expulsion: ");
		if (sortedTopList.isEmpty()) {
			System.out.println("");
		} else {
			for (int i = 0; i < sortedTopList.size(); i++) {
				System.out.print("Student " + sortedTopList.get(i));
				if (i < sortedTopList.size() - 1) {
					System.out.print(", ");
				}
			}
			System.out.println();
		}
	}

	private static void scountOutput(
		List<Student> students,
		List<Integer> topList
	) {
		System.out.println(
			"List of students for expulsion consists of " +
			topList.size() +
			" students"
		);
	}
}
