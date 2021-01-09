package poo.tema2;


/**
 * Clasa builder pentru Product
 */
public class ProductBuilder {
    private Product product;

    public ProductBuilder(){
        this.product = new Product();
    }

    public ProductBuilder withUniqueId(String id){
        product.setUniqueId(id);
        return this;
    }

    public ProductBuilder withName(String name){
        product.setName(name);
        return this;
    }

    public ProductBuilder withManufacturer(Manufacturer manufacturer){
        product.setManufacturer(manufacturer);
        return this;
    }

    public ProductBuilder withPrice(double price){
        product.setPrice(price);
        return this;
    }

    public ProductBuilder withQuantity(int quantity){
        product.setQuantity(quantity);
        return this;
    }

    public ProductBuilder withDiscount(Discount discount){
        product.setDiscount(discount);
        return this;
    }

    public Product build(){
        return product;
    }
}
