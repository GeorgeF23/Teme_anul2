package poo.tema2.Commands;

import poo.tema2.Currency;
import poo.tema2.Exceptions.CurrencyNotFoundException;
import poo.tema2.Store;


/**
 * Clasa care implementeaza comanda de setare a monedei curente din store
 */
public class SetStoreCurrency implements ICommand {
    private final Store store;
    private final String newCurrencyName;

    public SetStoreCurrency(Store store, String newCurrency) {
        this.store = store;
        this.newCurrencyName = newCurrency;
    }

    @Override
    public void execute() {
        Currency newCurrency = this.store.searchCurrencyByName(this.newCurrencyName);
        if(newCurrency == null){
            throw new CurrencyNotFoundException("Moneda nu exista in store!");
        }
        this.store.setCurrentCurrency(newCurrency);
    }
}
