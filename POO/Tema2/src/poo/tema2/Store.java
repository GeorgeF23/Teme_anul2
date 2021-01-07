package poo.tema2;

import java.util.ArrayList;

/**
 * The class that holds the information for the store.
 */
public class Store {
    private static Store instance;

    private ArrayList<Currency> currencies;
    private Currency currentCurrency;

    /**
     * Method that returns the instance of the store
     */
    public static Store getInstance(){
        if(instance == null){
            instance = new Store();
        }
        return instance;
    }

}
