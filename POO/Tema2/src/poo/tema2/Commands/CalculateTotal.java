package poo.tema2.Commands;

import poo.tema2.Product;
import poo.tema2.Store;

public class CalculateTotal implements ICommand{

    private Store store;
    private String[] productIds;

    public CalculateTotal(Store store, String ...productIds) {
        this.store = store;
        this.productIds = productIds;
    }

    @Override
    public void execute() {
        double total = 0;
        for(String id : this.productIds){
            Product product = this.store.searchProductByID(id);
            total += product.getPriceWithDiscount();
        }
        System.out.println(total);
    }
}
