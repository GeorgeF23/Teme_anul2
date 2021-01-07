package poo.tema2;

import java.util.ArrayList;

/**
 * The class that holds the information for the store.
 */
public class Store {
    private static Store instance;

    private ArrayList<Currency> currencies;
    private ArrayList<Manufacturer> manufacturers;
    private Currency currentCurrency;

    private Store(){
        this.currencies = new ArrayList<>();
        this.manufacturers = new ArrayList<>();

        this.currentCurrency = new Currency("EUR", "€", 1.0); // Moneda default in store
        this.currencies.add(this.currentCurrency);

        this.manufacturers.add(new Manufacturer("Not available")); // Producatorul care va fi asignat produselor din fisierul csv care nu au producator.
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

    /**
     * Getter pentru moneda curenta
     * @return
     */
    public Currency getCurrentCurrency() {
        return currentCurrency;
    }

    /**
     * Setter pentru moneda curenta
     * @param currentCurrency
     */
    public void setCurrentCurrency(Currency currentCurrency) {
        this.currentCurrency = currentCurrency;
    }

    /**
     * Getter pentru lista de monede
     * @return lista de monede
     */
    public ArrayList<Currency> getCurrencies() {
        return currencies;
    }

    /**
     * Cauta o moneda in store
     * @param name numele monedei pe care o cauta
     * @return moneda daca exista / null daca nu exista
     */
    public Currency searchCurrencyByName(String name){
        for(Currency c : this.currencies){
            if(c.getName().equals(name)){
                return c;
            }
        }
        return null;
    }

    public ArrayList<Manufacturer> getManufacturers() {
        return manufacturers;
    }
}
