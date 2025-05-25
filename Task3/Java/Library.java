import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringJoiner;

// Перечисление для типов команд (не используется напрямую в processCommand, но сохранено для соответствия)
enum Type {
	CREATE_TRAIN,
	TRAINS_FOR_TOWN,
	TOWNS_FOR_TRAIN,
	TRAINS,
	CREATE_TRAM,
	TRAMS_IN_STOP,
	STOPS_IN_TRAM,
	TRAMS,
	CREATE_PLANE,
	PLANES_FOR_TOWN,
	TOWNS_FOR_PLANE,
	PLANES,
	CREATE_TRL,
	TRL_IN_STOP,
	STOPS_IN_TRL,
	TRLS,
}

// Структура для трамвая (для варианта 2)
class Tram {

	String name;
	List<String> stops;

	public Tram(String name, List<String> stops) {
		this.name = name;
		this.stops = stops;
	}
}

public class Library {

	// Функция для обработки команд (для варианта 2 - трамваи)
	public static void processCommand(
		String command,
		String args,
		List<Tram> trams
	) {
		if (command.equals("CREATE_TRAM")) {
			String[] parts = args.split(" ", 2); // Разделяем имя трамвая и остальное
			String tramName = parts[0];

			String[] stopParts = parts[1].split(" "); // Разделяем количество остановок и сами остановки

			List<String> stops = new ArrayList<>();
			for (int i = 1; i < stopParts.length; i++) { // Начинаем с индекса 1, так как 0 - это количество
				stops.add(stopParts[i]);
			}
			trams.add(new Tram(tramName, stops));
		} else if (command.equals("TRAMS_IN_STOP")) {
			String stopName = args;
			List<String> tramsInThisStop = new ArrayList<>();
			for (Tram tram : trams) {
				for (String stop : tram.stops) {
					if (stop.equals(stopName)) {
						tramsInThisStop.add(tram.name);
						break;
					}
				}
			}
			if (tramsInThisStop.isEmpty()) {
				System.out.println("Trams is absent");
			} else {
				for (String tramName : tramsInThisStop) {
					System.out.println(tramName);
				}
			}
		} else if (command.equals("STOPS_IN_TRAM")) {
			String tramName = args;
			boolean found = false;
			for (Tram tram : trams) {
				if (tram.name.equals(tramName)) {
					found = true;
					Map<String, List<String>> stopsAndTrams = new HashMap<>();
					for (String stop : tram.stops) {
						stopsAndTrams.put(stop, new ArrayList<>()); // Инициализируем список для каждой остановки
						for (Tram otherTram : trams) {
							if (!otherTram.name.equals(tramName)) { // Исключаем текущий трамвай
								for (String otherStop : otherTram.stops) {
									if (otherStop.equals(stop)) {
										stopsAndTrams
											.get(stop)
											.add(otherTram.name);
									}
								}
							}
						}
					}
					for (String stop : tram.stops) {
						System.out.print("Stop " + stop + ": ");
						List<String> tramsForStop = stopsAndTrams.get(stop);
						if (tramsForStop != null && !tramsForStop.isEmpty()) {
							StringJoiner sj = new StringJoiner(" ");
							for (String tName : tramsForStop) {
								sj.add(tName);
							}
							System.out.println(sj.toString());
						} else {
							System.out.println("0");
						}
					}
					break;
				}
			}
			if (!found) {
				System.out.println("Trams is absent");
			}
		} else if (command.equals("TRAMS")) {
			if (trams.isEmpty()) {
				System.out.println("Trams is absent");
			} else {
				for (Tram tram : trams) {
					System.out.print("TRAM " + tram.name + ":");
					for (String stop : tram.stops) {
						System.out.print(" " + stop);
					}
					System.out.println();
				}
			}
		}
	}
}
