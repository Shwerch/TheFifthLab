import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Main {

	public static void main(String[] args) {
		String filename = "data.conf";
		try (
			BufferedReader reader = new BufferedReader(new FileReader(filename))
		) {
			int numCommands = Integer.parseInt(reader.readLine());

			List<Student> students = new ArrayList<>(); // Все студенты
			List<Integer> topList = new ArrayList<>(); // ID студентов в списке на отчисление

			String line;
			for (int i = 0; i < numCommands; i++) {
				if ((line = reader.readLine()) != null) {
					Library.processCommand(line, students, topList);
				}
			}
		} catch (IOException e) {
			System.err.println(
				"Не удалось открыть файл " + filename + ": " + e.getMessage()
			);
		} catch (NumberFormatException e) {
			System.err.println(
				"Ошибка формата числа в файле data.conf: " + e.getMessage()
			);
		}
	}
}
