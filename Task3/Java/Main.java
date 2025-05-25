import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Main {

	public static void main(String[] args) {
		List<Tram> trams = new ArrayList<>(); // Для варианта 2 (трамваи)

		// Открываем файл для чтения. Убедитесь, что "data.conf" находится в той же директории, что и исполняемый файл.
		try (
			BufferedReader inputFile = new BufferedReader(
				new FileReader("data.conf")
			)
		) {
			String line;
			while ((line = inputFile.readLine()) != null) {
				String[] parts = line.split(" ", 2); // Разделяем команду и аргументы
				String command = parts[0];
				String myArgs = parts.length > 1 ? parts[1] : ""; // Аргументы, если есть

				Library.processCommand(command, myArgs, trams);
			}
		} catch (IOException e) {
			System.err.println(
				"Не удалось открыть файл data.conf: " + e.getMessage()
			);
			System.exit(1); // Завершаем программу с ошибкой
		}
	}
}
