package poo.tema2.Commands;

import poo.tema2.Currency;
import poo.tema2.Store;


/**
 * Clasa care implementeaza comanda care afiseaza toate monedele din store
 */
public class ListCurrencies implements ICommand{

    private final Store store;

    public ListCurrencies(Store store){
        this.store = store;
    }

    @Override
    public void execute() {
        for(Currency c : store.getCurrencies()){
            System.out.println(c.getName() + " " + c.getParityToEur());
        }
    }
}
