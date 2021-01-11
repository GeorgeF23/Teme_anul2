package poo.tema2.Commands;

import poo.tema2.Exceptions.DuplicateCurrencyException;
import poo.tema2.Store;
import poo.tema2.Currency;


/**
 * Clasa care implementeaza comanda de adaugare a unei noi monede in store
 */
public class AddCurrency implements ICommand {

    private final Store store;
    private final Currency newCurrency;

    public AddCurrency(Store store, Currency newCurrency){
        this.store = store;
        this.newCurrency = newCurrency;
    }


    /**
     * Adauga o moneda noua in store
     */
    @Override
    public void execute() {
        if(store.searchCurrencyByName(this.newCurrency.getName()) != null){
            throw new DuplicateCurrencyException("Moneda exista deja in magazin!");
        }
        this.store.getCurrencies().add(this.newCurrency);
    }
}
