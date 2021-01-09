package poo.tema2.Commands;

import poo.tema2.Discount;
import poo.tema2.DiscountType;
import poo.tema2.Store;

public class AddDiscount implements ICommand {

    private Store store;
    private Discount discount;

    public AddDiscount(Store store, String type, String value, String[] nameSplitted) {
        this.store = store;
        this.discount = new Discount(DiscountType.valueOf(type), Double.parseDouble(value), String.join(" " ,nameSplitted));
    }

    @Override
    public void execute() {
        this.store.getDiscounts().add(this.discount);
    }
}
