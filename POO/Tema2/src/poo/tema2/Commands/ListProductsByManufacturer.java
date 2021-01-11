package poo.tema2.Commands;

import poo.tema2.Product;
import poo.tema2.Store;


/**
 * Clasa care implementeaza comanda de afisare a produselor ce apartin unui producator
 */
public class ListProductsByManufacturer implements ICommand {

    private final Store store;
    private final String manufacturerName;

    public ListProductsByManufacturer(Store store, String manufacturerName) {
        this.store = store;
        this.manufacturerName = manufacturerName;
    }

    @Override
    public void execute() {
        for(Product product : this.store.getProducts()){
            if(product.getManufacturer().getName().equals(this.manufacturerName)){
                System.out.println(product.getUniqueId() + "," + product.getName() + "," + product.getManufacturer().getName() + ","
                        + this.store.getCurrentCurrency().getSymbol() + product.getPrice() + "," + product.getQuantity());
            }
        }
    }
}
