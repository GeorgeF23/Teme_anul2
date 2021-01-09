package poo.tema2;

import java.time.LocalDateTime;


/**
 * Clasa ce descrie un discount
 */
public class Discount {
    private final String name;
    private final DiscountType type;
    private final double value;
    private LocalDateTime lastDateApplied;

    public Discount(DiscountType type, double value, String name) {
        this.name = name;
        this.type = type;
        this.value = value;
    }

    public String getName() {
        return name;
    }

    public double getValue() {
        return value;
    }

    public DiscountType getType() {
        return type;
    }

    public void setLastDateApplied(LocalDateTime lastDateApplied) {
        this.lastDateApplied = lastDateApplied;
    }

    @Override
    public String toString() {
        return "Discount: " +
                "name='" + name + '\'' +
                ", type=" + type +
                ", value=" + value +
                ", lastDateApplied=" + lastDateApplied;
    }
}
