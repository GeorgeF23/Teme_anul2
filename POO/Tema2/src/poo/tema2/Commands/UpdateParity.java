package poo.tema2.Commands;

import poo.tema2.Currency;
import poo.tema2.Exceptions.CurrencyNotFoundException;
import poo.tema2.Store;

/**
 * Clasa care implementeaza comanda de actualizare a paritatii unei monede
 */
public class UpdateParity implements ICommand{
    private Store store;
    private String currencyName;
    private double newValue;

    public UpdateParity(Store store, String currencyName, double newValue){
        this.store = store;
        this.currencyName = currencyName;
        this.newValue = newValue;
    }

    @Override
    public void execute() {
        Currency currency = this.store.searchCurrencyByName(this.currencyName);
        if(currency == null){
            throw new CurrencyNotFoundException("Moneda nu se afla in store!");
        }
        currency.setParityToEur(this.newValue);
    }
}
