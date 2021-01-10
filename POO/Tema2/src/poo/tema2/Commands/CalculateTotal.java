package poo.tema2.Commands;

import poo.tema2.Product;
import poo.tema2.Store;


/**
 * Clasa care implementeaza comanda de calcul al pretului produselor
 */
public class CalculateTotal implements ICommand{

    private final Store store;
    private final String[] productIds;

    public CalculateTotal(Store store, String ...productIds) {
        this.store = store;
        this.productIds = productIds;
    }

    @Override
    public void execute() {
        double total = 0;
        for(String id : this.productIds){
            Product product = this.store.searchProductByID(id);
            if(product != null){
                total += product.getPriceWithDiscount();
            }
        }
        System.out.println(this.store.getCurrentCurrency().getSymbol() + total);
    }
}
