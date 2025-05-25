// Cell.java
public class Cell {
    private String itemName;
    private int quantity;
    private final int maxCapacity = 10;

    public Cell() {
        this.itemName = "";
        this.quantity = 0;
    }

    public String getItemName() {
        return itemName;
    }

    public void setItemName(String itemName) {
        this.itemName = itemName;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public int getMaxCapacity() {
        return maxCapacity;
    }

    public boolean isEmpty() {
        return quantity == 0;
    }
}
