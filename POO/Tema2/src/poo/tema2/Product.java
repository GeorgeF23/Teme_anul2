package poo.tema2;


/**
 * Clasa ce descrie un produs
 */
public class Product {
    private String uniqueId;
    private String name;
    private Manufacturer manufacturer;
    private double price;
    private int quantity;
    private Discount discount;

    public String getUniqueId() {
        return uniqueId;
    }

    public void setUniqueId(String uniqueId) {
        this.uniqueId = uniqueId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Manufacturer getManufacturer() {
        return manufacturer;
    }

    public void setManufacturer(Manufacturer manufacturer) {
        this.manufacturer = manufacturer;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public Discount getDiscount() {
        return discount;
    }

    public void setDiscount(Discount discount) {
        this.discount = discount;
    }

    /**
     * Calculeaza pretul produsului tinand cont de discount
     * @return pretul produsului
     */
    public double getPriceWithDiscount(){
        if(this.discount != null){
            return switch (this.discount.getType()) {
                case PERCENTAGE -> this.price * (1 - this.discount.getValue() / 100);
                case FIXED -> this.price - this.discount.getValue();
            };
        }
        return this.price > 0 ? this.price : 0;
    }

    @Override
    public String toString() {
        return "";
    }
}
