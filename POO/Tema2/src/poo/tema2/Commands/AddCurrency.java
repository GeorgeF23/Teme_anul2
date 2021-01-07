package poo.tema2.Commands;

import poo.tema2.Exceptions.DuplicateCurrencyException;
import poo.tema2.Store;
import poo.tema2.Currency;

public class AddCurrency implements ICommand {

    private Store store;
    private Currency newCurrency;

    public AddCurrency(Store store, Currency newCurrency){
        this.store = store;
        this.newCurrency = newCurrency;
    }


    @Override
    public void execute() {
        if(store.searchCurrencyByName(this.newCurrency.getName()) != null){
            throw new DuplicateCurrencyException("Moneda exista deja in magazin!");
        }
        this.store.getCurrencies().add(this.newCurrency);
    }
}
