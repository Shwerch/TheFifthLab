import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Random;

public class QueueManager {

	private int numWindows;
	private List<Patient> patients;
	private List<Integer> ticketNumbersPool;
	private Random rng;

	public QueueManager(int numWindows) {
		this.numWindows = numWindows;
		this.patients = new ArrayList<>();
		this.ticketNumbersPool = new ArrayList<>();
		this.rng = new Random();

		for (int i = 100; i <= 999; i++) {
			ticketNumbersPool.add(i);
		}
		Collections.shuffle(ticketNumbersPool, rng);
	}

	private String generateTicketNumber() {
		if (ticketNumbersPool.isEmpty()) {
			throw new RuntimeException("Kernel panic");
		}

		int num = ticketNumbersPool.remove(ticketNumbersPool.size() - 1);

		return String.format("T%03d", num);
	}

	public String enqueue(int duration) {
		Patient patient = new Patient(generateTicketNumber(), duration);
		patients.add(patient);
		return patient.ticketNumber;
	}

	public void distributeQueue() {
		patients.sort(
			Comparator.comparingInt((Patient p) -> p.duration).reversed()
		);

		int[] windowTotalDurations = new int[numWindows];
		for (int i = 0; i < numWindows; i++) {
			windowTotalDurations[i] = 0;
		}

		List<List<Patient>> windowAssignments = new ArrayList<>();
		for (int i = 0; i < numWindows; i++) {
			windowAssignments.add(new ArrayList<>());
		}

		for (Patient patient : patients) {
			int minDuration = Integer.MAX_VALUE;
			int minDurationWindowIdx = -1;

			for (int i = 0; i < numWindows; i++) {
				if (windowTotalDurations[i] < minDuration) {
					minDuration = windowTotalDurations[i];
					minDurationWindowIdx = i;
				}
			}

			if (minDurationWindowIdx != -1) {
				windowAssignments.get(minDurationWindowIdx).add(patient);
				windowTotalDurations[minDurationWindowIdx] += patient.duration;
			}
		}

		for (int i = 0; i < numWindows; i++) {
			System.out.print(
				">>> Окно " +
				(i + 1) +
				" (" +
				windowTotalDurations[i] +
				" минут): "
			);
			boolean firstPatient = true;
			for (Patient patient : windowAssignments.get(i)) {
				if (!firstPatient) {
					System.out.print(", ");
				}
				System.out.print(patient.ticketNumber);
				firstPatient = false;
			}
			System.out.println();
		}
	}
}
