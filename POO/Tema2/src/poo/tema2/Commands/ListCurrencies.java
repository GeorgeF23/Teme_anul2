package poo.tema2.Commands;

import poo.tema2.Currency;
import poo.tema2.Store;

public class ListCurrencies implements ICommand{

    private Store store;

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
