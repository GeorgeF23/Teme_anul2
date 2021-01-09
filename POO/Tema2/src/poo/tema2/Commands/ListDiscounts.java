package poo.tema2.Commands;

import poo.tema2.Discount;
import poo.tema2.Store;

public class ListDiscounts implements ICommand {

    private Store store;

    public ListDiscounts(Store store) {
        this.store = store;
    }

    @Override
    public void execute() {
        for(Discount discount : this.store.getDiscounts()){
            System.out.println(discount);
        }
    }
}
