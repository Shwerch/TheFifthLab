// Library.java
import java.util.ArrayList;
import java.util.HashMap;
import java.util.InputMismatchException;
import java.util.Map;
import java.util.Scanner;

public class Library {
    // Global warehouse structure
    private static Map<Character, ArrayList<ArrayList<ArrayList<Cell>>>> warehouse;

    public static void initializeWarehouse() {
        warehouse = new HashMap<>();
        // Initialize only zone 'A'
        char zoneChar = 'A';
        ArrayList<ArrayList<ArrayList<Cell>>> racks = new ArrayList<>();
        for (int i = 0; i < 10; i++) { // 10 racks
            ArrayList<ArrayList<Cell>> sections = new ArrayList<>();
            for (int j = 0; j < 7; j++) { // 7 vertical sections
                ArrayList<Cell> shelves = new ArrayList<>();
                for (int k = 0; k < 4; k++) { // 4 shelves
                    shelves.add(new Cell());
                }
                sections.add(shelves);
            }
            racks.add(sections);
        }
        warehouse.put(zoneChar, racks);
    }

    private static Cell getCellFromAddress(String address) {
        if (address.length() < 4) {
            return null; // Invalid address format
        }

        char zoneChar = address.charAt(0);
        // Only allow 'A' zone
        if (zoneChar != 'A') {
            return null; // Invalid zone
        }

        try {
            // Extract rack, section, and shelf numbers from the address string
            // This part requires careful parsing as rack number can be 1 or 2 digits
            int rackNum;
            int sectionNum;
            int shelfNum;

            if (address.length() == 4) { // e.g., A173
                rackNum = Character.getNumericValue(address.charAt(1));
                sectionNum = Character.getNumericValue(address.charAt(2));
                shelfNum = Character.getNumericValue(address.charAt(3));
            } else if (address.length() == 5) { // e.g., A1039
                rackNum = Integer.parseInt(address.substring(1, 3));
                sectionNum = Character.getNumericValue(address.charAt(3));
                shelfNum = Character.getNumericValue(address.charAt(4));
            } else {
                return null; // Address too long or short
            }


            if (rackNum < 1 || rackNum > 10 ||
                    sectionNum < 1 || sectionNum > 7 ||
                    shelfNum < 1 || shelfNum > 4) {
                return null; // Out of bounds
            }

            // Adjust to 0-based indexing
            return warehouse.get(zoneChar).get(rackNum - 1).get(sectionNum - 1).get(shelfNum - 1);

        } catch (NumberFormatException | IndexOutOfBoundsException e) {
            return null; // Conversion or indexing error
        }
    }

    private static String getAddressFromIndices(char zoneChar, int rackIdx, int sectionIdx, int shelfIdx) {
        return String.valueOf(zoneChar) + (rackIdx + 1) + (sectionIdx + 1) + (shelfIdx + 1);
    }

    public static void add_item(String itemName, int quantity, String address) {
        Cell cell = getCellFromAddress(address);
        if (cell == null) {
            System.out.println("Error: Invalid address '" + address + "'.");
            return;
        }

        if (cell.isEmpty()) {
            if (quantity > cell.getMaxCapacity()) {
                System.out.println("Error: Cannot add " + quantity + " units. Cell capacity is " + cell.getMaxCapacity() + ".");
                return;
            }
            cell.setItemName(itemName);
            cell.setQuantity(quantity);
            System.out.println("Added " + quantity + " " + itemName + " to " + address + ".");
        } else if (!cell.getItemName().equals(itemName)) {
            System.out.println("Error: Cell " + address + " already contains '" + cell.getItemName() + "'. Cannot add '" + itemName + "'.");
        } else {
            if (cell.getQuantity() + quantity > cell.getMaxCapacity()) {
                System.out.println("Error: Adding " + quantity + " units would exceed cell capacity (" + cell.getMaxCapacity() + "). Current: " + cell.getQuantity() + ".");
                return;
            }
            cell.setQuantity(cell.getQuantity() + quantity);
            System.out.println("Added " + quantity + " " + itemName + " to " + address + ". Total: " + cell.getQuantity() + ".");
        }
    }

    public static void remove_item(String itemName, int quantity, String address) {
        Cell cell = getCellFromAddress(address);
        if (cell == null) {
            System.out.println("Error: Invalid address '" + address + "'.");
            return;
        }

        if (cell.isEmpty() || !cell.getItemName().equals(itemName)) {
            System.out.println("Error: Cell " + address + " does not contain '" + itemName + "'.");
            return;
        }

        if (cell.getQuantity() < quantity) {
            System.out.println("Error: Insufficient quantity of '" + itemName + "' in cell " + address + ". Available: " + cell.getQuantity() + ".");
            return;
        }

        cell.setQuantity(cell.getQuantity() - quantity);
        System.out.println("Removed " + quantity + " " + itemName + " from " + address + ".");
        if (cell.getQuantity() == 0) {
            cell.setItemName("");
            System.out.println("Cell " + address + " is now empty.");
        }
    }

    public static void display_info() {
        int totalCapacity = 0;
        int totalOccupied = 0;

        char zoneChar = 'A'; // Only process zone 'A'

        int zoneCapacity = 0;
        int zoneOccupied = 0;

        // Calculate total and zone capacities and occupied quantities
        ArrayList<ArrayList<ArrayList<Cell>>> racks = warehouse.get(zoneChar);
        if (racks != null) {
            for (ArrayList<ArrayList<Cell>> rack : racks) {
                for (ArrayList<Cell> section : rack) {
                    for (Cell cell : section) {
                        totalCapacity += cell.getMaxCapacity();
                        zoneCapacity += cell.getMaxCapacity();
                        if (!cell.isEmpty()) {
                            totalOccupied += cell.getQuantity();
                            zoneOccupied += cell.getQuantity();
                        }
                    }
                }
            }
        }

        // Overall warehouse loading percentage
        double warehouseLoadPercent = (totalCapacity == 0) ? 0 : (double) totalOccupied / totalCapacity * 100;
        System.out.println("\n--- Warehouse Information ---");
        System.out.printf("Warehouse Loading: %.2f%%\n", warehouseLoadPercent);

        // Zone loading percentage for 'A'
        double zoneLoadPercent = (zoneCapacity == 0) ? 0 : (double) zoneOccupied / zoneCapacity * 100;
        System.out.printf("Zone %c Loading: %.2f%%\n", zoneChar, zoneLoadPercent);


        System.out.println("\n--- Occupied Cells ---");
        if (racks != null) {
            for (int rackIdx = 0; rackIdx < racks.size(); ++rackIdx) {
                for (int sectionIdx = 0; sectionIdx < racks.get(rackIdx).size(); ++sectionIdx) {
                    for (int shelfIdx = 0; shelfIdx < racks.get(rackIdx).get(sectionIdx).size(); ++shelfIdx) {
                        Cell cell = racks.get(rackIdx).get(sectionIdx).get(shelfIdx);
                        if (!cell.isEmpty()) {
                            System.out.println(getAddressFromIndices(zoneChar, rackIdx, sectionIdx, shelfIdx)
                                    + ": " + cell.getItemName() + " (" + cell.getQuantity() + " units)");
                        }
                    }
                }
            }
        }

        System.out.println("\n--- Empty Cells ---");
        System.out.println("Zone " + zoneChar + ":");
        if (racks != null) {
            for (int rackIdx = 0; rackIdx < 10; ++rackIdx) {
                for (int shelfIdx = 0; shelfIdx < 4; ++shelfIdx) { // Iterate shelves for row output
                    for (int sectionIdx = 0; sectionIdx < 7; ++sectionIdx) {
                        Cell cell = warehouse.get(zoneChar).get(rackIdx).get(sectionIdx).get(shelfIdx);
                        if (cell.isEmpty()) {
                            System.out.printf("%-8s", getAddressFromIndices(zoneChar, rackIdx, sectionIdx, shelfIdx));
                        } else {
                            System.out.printf("%-8s", ""); // Print empty space if cell is not empty
                        }
                    }
                    System.out.println();
                }
            }
        }
        System.out.println("----------------------------");
    }

    public static void processCommand(String commandLine) {
        Scanner commandScanner = new Scanner(commandLine);
        if (!commandScanner.hasNext()) {
            System.out.println("Empty command.");
            commandScanner.close();
            return;
        }

        String command = commandScanner.next();

        if (command.equalsIgnoreCase("ADD")) {
            if (commandScanner.hasNext()) {
                String itemName = commandScanner.next();
                if (commandScanner.hasNextInt()) {
                    int quantity = commandScanner.nextInt();
                    if (commandScanner.hasNext()) {
                        String address = commandScanner.next();
                        add_item(itemName, quantity, address);
                    } else {
                        System.out.println("Missing address for ADD command.");
                    }
                } else {
                    System.out.println("Missing quantity for ADD command.");
                }
            } else {
                System.out.println("Missing item name for ADD command.");
            }
        } else if (command.equalsIgnoreCase("REMOVE")) {
            if (commandScanner.hasNext()) {
                String itemName = commandScanner.next();
                if (commandScanner.hasNextInt()) {
                    int quantity = commandScanner.nextInt();
                    if (commandScanner.hasNext()) {
                        String address = commandScanner.next();
                        remove_item(itemName, quantity, address);
                    } else {
                        System.out.println("Missing address for REMOVE command.");
                    }
                } else {
                    System.out.println("Missing quantity for REMOVE command.");
                }
            } else {
                System.out.println("Missing item name for REMOVE command.");
            }
        } else if (command.equalsIgnoreCase("INFO")) {
            display_info();
        } else {
            System.out.println("Unknown command: " + command);
        }
        commandScanner.close();
    }
}
