package poo.tema2;


/**
 * Clasa care construieste un produs nou
 */
public class ProductBuilder {
    private Product product;

    /**
     * Initializeaza un produs nou
     */
    public ProductBuilder(){
        this.product = new Product();
    }

    /**
     * Seteaza id-ul produsului
     */
    public ProductBuilder withUniqueId(String id){
        product.setUniqueId(id);
        return this;
    }

    /**
     * Seteaza numele produsului
     */
    public ProductBuilder withName(String name){
        product.setName(name);
        return this;
    }

    /**
     * Seteaza producatorul produsului
     */
    public ProductBuilder withManufacturer(Manufacturer manufacturer){
        product.setManufacturer(manufacturer);
        return this;
    }

    /**
     * Seteaza pretul produsului
     */
    public ProductBuilder withPrice(double price){
        product.setPrice(price);
        return this;
    }

    /**
     * Seteaza cantitatea disponibila in stock a produsului
     */
    public ProductBuilder withQuantity(int quantity){
        product.setQuantity(quantity);
        return this;
    }

    /**
     * Seteaza discountul produsului
     */
    public ProductBuilder withDiscount(Discount discount){
        product.setDiscount(discount);
        return this;
    }

    /**
     * Finalizeaza constructia produsului
     * @return produsul nou construit
     */
    public Product build(){
        return product;
    }
}
