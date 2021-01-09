package poo.tema2.Commands;

import poo.tema2.Product;
import poo.tema2.Store;


/**
 * Clasa care implementeaza comanda de afisare a informatiilor unui produs
 */
public class ShowProduct implements ICommand{

    private final Store store;
    private final String productId;

    public ShowProduct(Store store, String productId) {
        this.store = store;
        this.productId = productId;
    }

    @Override
    public void execute() {
        Product product = this.store.searchProductByID(this.productId);
        System.out.println(product.getUniqueId() + "," + product.getName() + "," + product.getManufacturer().getName() + ","
                + this.store.getCurrentCurrency().getSymbol() + product.getPrice() + "," + product.getQuantity());
    }
}
