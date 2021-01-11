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

    /**
     * Getter pentru id-ul produsului
     * @return id-ul produsului
     */
    public String getUniqueId() {
        return uniqueId;
    }

    /**
     * Setter pentru id-ul produsului
     * @param uniqueId noul id
     */
    public void setUniqueId(String uniqueId) {
        this.uniqueId = uniqueId;
    }

    /**
     * Getter pentru numele produsului
     * @return numele produsului
     */
    public String getName() {
        return name;
    }

    /**
     * Setter pentru numele produsului
     * @param name noul numele produsului
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Getter pentru producatorul produsului
     * @return producatorul produsului
     */
    public Manufacturer getManufacturer() {
        return manufacturer;
    }

    /**
     * Setter pentru producatorul produsului
     * @param manufacturer noul producator
     */
    public void setManufacturer(Manufacturer manufacturer) {
        this.manufacturer = manufacturer;
    }

    /**
     * Getter pentru pretul produsului
     * @return pretul produsului
     */
    public double getPrice() {
        return price;
    }

    /**
     * Setter pentru pretul produsului
     * @param price noul pret
     */
    public void setPrice(double price) {
        this.price = price;
    }

    /**
     * Getter pentru cantitatea disponibila in stock a produsului
     * @return cantitatea disponibila in stock a produsului
     */
    public int getQuantity() {
        return quantity;
    }

    /**
     * Setter pentru cantitatea disponibila in stock a produsului
     * @param quantity noua cantitate disponibila in stock
     */
    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    /**
     * Getter pentru discountul produsului
     * @return discountul produsului
     */
    public Discount getDiscount() {
        return discount;
    }

    /**
     * Setter pentru discountul produsului
     * @param discount noul discount
     */
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
}
