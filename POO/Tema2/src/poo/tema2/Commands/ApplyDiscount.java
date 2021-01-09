package poo.tema2.Commands;

import poo.tema2.Discount;
import poo.tema2.DiscountType;
import poo.tema2.Exceptions.DiscountNotFoundException;
import poo.tema2.Product;
import poo.tema2.Store;

import java.time.LocalDateTime;

public class ApplyDiscount implements ICommand {

    private Store store;
    private DiscountType type;
    private double value;

    public ApplyDiscount(Store store, String type, String value) {
        this.store = store;
        this.type = DiscountType.valueOf(type);
        this.value = Double.parseDouble(value);
    }


    @Override
    public void execute() {
        Discount discount = this.store.searchDiscountByTypeAndValue(this.type, this.value);
        if(discount == null){
            throw new DiscountNotFoundException("Discount-ul nu a fost gasit");
        }

        for(Product product : this.store.getProducts()){
            product.setDiscount(discount);
        }

        discount.setLastDateApplied(LocalDateTime.now());
    }
}
