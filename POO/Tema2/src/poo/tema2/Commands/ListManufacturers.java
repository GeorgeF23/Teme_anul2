package poo.tema2.Commands;

import poo.tema2.Manufacturer;
import poo.tema2.Store;


/**
 * Clasa care implementeaza comanda de afisare a prodcatorilor din store
 */
public class ListManufacturers implements ICommand {
    private final Store store;

    public ListManufacturers(Store store) {
        this.store = store;
    }

    @Override
    public void execute() {
        for(Manufacturer m : this.store.getManufacturers()){
            System.out.println(m.getName() + " " + m.getCountProducts());
        }
    }
}
