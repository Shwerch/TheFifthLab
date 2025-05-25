import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.Comparator;
// import java.util.AbstractMap; // Not strictly needed if we use int arrays for window loads

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

        // Populate the pool with numbers from 100 to 999
        for (int i = 100; i <= 999; i++) {
            ticketNumbersPool.add(i);
        }
        // Shuffle the pool
        Collections.shuffle(ticketNumbersPool, rng);
    }

    private String generateTicketNumber() {
        if (ticketNumbersPool.isEmpty()) {
            // Handle the case where all ticket numbers are used up
            return "TXXX"; // Or throw an exception, depending on desired behavior
        }

        int num = ticketNumbersPool.remove(ticketNumbersPool.size() - 1); // Get and remove the last element

        // Format to "T" + three digits, padded with leading zeros if necessary
        return String.format("T%03d", num);
    }

    public String enqueue(int duration) {
        Patient patient = new Patient(generateTicketNumber(), duration);
        patients.add(patient);
        return patient.ticketNumber;
    }

    public void distributeQueue() {
        // Sort patients by duration in descending order
        patients.sort(Comparator.comparingInt((Patient p) -> p.duration).reversed());

        // Keep track of the total duration for each window
        // The index of this array corresponds to the window index (0 to numWindows - 1)
        int[] windowTotalDurations = new int[numWindows];
        // Initialize all window durations to 0
        for (int i = 0; i < numWindows; i++) {
            windowTotalDurations[i] = 0;
        }

        // Initialize windowAssignments with 'numWindows' empty ArrayLists
        List<List<Patient>> windowAssignments = new ArrayList<>();
        for (int i = 0; i < numWindows; i++) {
            windowAssignments.add(new ArrayList<>());
        }

        for (Patient patient : patients) {
            int minDuration = Integer.MAX_VALUE;
            int minDurationWindowIdx = -1;

            // Find the window with the minimum current total duration
            for (int i = 0; i < numWindows; i++) {
                if (windowTotalDurations[i] < minDuration) {
                    minDuration = windowTotalDurations[i];
                    minDurationWindowIdx = i;
                }
            }

            // Assign the patient to the window with the minimum duration
            if (minDurationWindowIdx != -1) { // Should always be true if numWindows > 0
                windowAssignments.get(minDurationWindowIdx).add(patient);
                windowTotalDurations[minDurationWindowIdx] += patient.duration;
            }
        }

        // Print the distribution
        for (int i = 0; i < numWindows; i++) {
            // totalDuration is already stored in windowTotalDurations[i]
            System.out.print(">>> Окно " + (i + 1) + " (" + windowTotalDurations[i] + " минут): ");
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
