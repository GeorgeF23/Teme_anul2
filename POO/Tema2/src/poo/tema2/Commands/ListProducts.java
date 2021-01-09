package poo.tema2.Commands;

import poo.tema2.Product;
import poo.tema2.Store;

public class ListProducts implements ICommand {
    private Store store;

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
