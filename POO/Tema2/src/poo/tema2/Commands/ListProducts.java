package poo.tema2.Commands;

import poo.tema2.Product;
import poo.tema2.Store;


/**
 * Clasa care implementeaza comanda de afisare a prodselor din store
 */
public class ListProducts implements ICommand {
    private final Store store;

    public ListProducts(Store store) {
        this.store = store;
    }

    @Override
    public void execute() {
        for(Product product : this.store.getProducts()){
            System.out.println(product.getUniqueId() + "," + product.getName() + "," + product.getManufacturer().getName() + ","
                    + this.store.getCurrentCurrency().getSymbol() + product.getPrice() + "," + product.getQuantity());
        }
    }
}
