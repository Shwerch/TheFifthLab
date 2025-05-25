import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);

		System.out.println(">>> Введите кол-во окон");
		int numWindows = scanner.nextInt();
		scanner.nextLine();

		QueueManager queueManager = new QueueManager(numWindows);
		String line;

		while (true) {
			System.out.print("<<< ");
			line = scanner.nextLine();

			if (line.startsWith("ENQUEUE")) {
				String[] parts = line.split(" ");
				if (parts.length > 1) {
					try {
						int duration = Integer.parseInt(parts[1]);
						System.out.println(
							">>> " + queueManager.enqueue(duration)
						);
					} catch (NumberFormatException e) {
						System.out.println(
							"Invalid duration. Please enter a number."
						);
					}
				}
			} else if (line.equals("DISTRIBUTE")) {
				queueManager.distributeQueue();
				break;
			}
		}
		scanner.close();
	}
}
