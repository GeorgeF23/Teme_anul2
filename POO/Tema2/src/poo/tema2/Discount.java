package poo.tema2;

import java.time.LocalDateTime;


/**
 * Clasa care descrie un discount
 */
public class Discount {
    private final String name;
    private final DiscountType type;
    private final double value;
    private LocalDateTime lastDateApplied;

    /**
     * Creaza un discount nou
     * @param type tipul discountului ("PERCENTAGE" / "FIXED")
     * @param value valoarea discountului
     * @param name numele discountului
     */
    public Discount(DiscountType type, double value, String name) {
        this.name = name;
        this.type = type;
        this.value = value;
    }

    /**
     * Getter pentru numele discountului
     * @return numele discountului
     */
    public String getName() {
        return name;
    }

    /**
     * Getter pentru valoarea discountului
     * @return valoarea discountului
     */
    public double getValue() {
        return value;
    }

    /**
     * Getter pentru tipul discountului
     * @return tipul discountului
     */
    public DiscountType getType() {
        return type;
    }

    /**
     * Setter pentru data aplicarii discountului
     * @param lastDateApplied data aplicarii discountului
     */
    public void setLastDateApplied(LocalDateTime lastDateApplied) {
        this.lastDateApplied = lastDateApplied;
    }

    /**
     * Creeaza un string cu detaliile discountului
     */
    @Override
    public String toString() {
        return "Discount: " +
                "name='" + name + '\'' +
                ", type=" + type +
                ", value=" + value +
                ", lastDateApplied=" + lastDateApplied;
    }
}
