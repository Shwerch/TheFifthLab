// Main.java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Library.initializeWarehouse();
        Scanner scanner = new Scanner(System.in);
        String commandLine;

        while (true) {
            System.out.print("> ");
            commandLine = scanner.nextLine();
            if (commandLine.equalsIgnoreCase("EXIT")) {
                break;
            }
            Library.processCommand(commandLine);
        }
        scanner.close();
    }
}
