package poo.tema2;

import java.util.ArrayList;

/**
 * The class that holds the information for the store.
 */
public class Store {
    private static Store instance;

    private ArrayList<Currency> currencies;
    private Currency currentCurrency;

    private Store(){
        this.currencies = new ArrayList<>();

        this.currentCurrency = new Currency("EUR", "€", 1.0);
        this.currencies.add(this.currentCurrency);
    }


    /**
     * Method that returns the instance of the store
     */
    public static Store getInstance(){
        if(instance == null){
            instance = new Store();
        }
        return instance;
    }

    public Currency getCurrentCurrency() {
        return currentCurrency;
    }

    public ArrayList<Currency> getCurrencies() {
        return currencies;
    }

    public Currency searchCurrencyByName(String name){
        for(Currency c : this.currencies){
            if(c.getName().equals(name)){
                return c;
            }
        }
        return null;
    }
}
