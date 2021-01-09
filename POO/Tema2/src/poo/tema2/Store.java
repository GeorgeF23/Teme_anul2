package poo.tema2;

import poo.tema2.Exceptions.DuplicateManufacturerException;
import poo.tema2.Exceptions.DuplicateProductException;
import poo.tema2.Exceptions.NegativePriceException;

import java.util.ArrayList;

/**
 * The class that holds the information for the store.
 */
public class Store {
    private static Store instance;

    private ArrayList<Currency> currencies;
    private ArrayList<Manufacturer> manufacturers;
    private ArrayList<Product> products;
    private ArrayList<Discount> discounts;
    private Currency currentCurrency;

    private Store(){
        this.currencies = new ArrayList<>();
        this.manufacturers = new ArrayList<>();
        this.products = new ArrayList<>();
        this.discounts = new ArrayList<>();

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
     * @param desiredCurrency
     */
    public void setCurrentCurrency(Currency desiredCurrency) {
        for(Product product : this.products){
            product.setPrice(Store.convertCurrency(product.getPrice(), this.currentCurrency, desiredCurrency));
        }
        this.currentCurrency = desiredCurrency;
    }

    /**
     * Getter pentru lista de monede
     * @return lista de monede
     */
    public ArrayList<Currency> getCurrencies() {
        return currencies;
    }

    /**
     * Getter pentru lista de produse
     * @return lista de produse
     */
    public ArrayList<Product> getProducts() {
        return products;
    }

    /**
     * Getter pentru lista de discount-uri
     * @return lista de discount-uri
     */
    public ArrayList<Discount> getDiscounts() {
        return discounts;
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

    /**
     * Cauta un producator dupa nume. Daca nu are nume, atunci returneaza prodcatorul default.
     * @param name numele produsului
     * @return producatorul gasit
     */
    public Manufacturer searchManufacturerByName(String name){
        if(name.equals("")){
            return this.manufacturers.get(0);   // Returnez producatorul "Not available"
        }
        for(Manufacturer m : this.manufacturers){
            if(m.getName().equals(name)){
                return m;
            }
        }
        return null;
    }

    /**
     * Adauga un prodcator nou in lista de prodcatori. Totodata se verifica daca exista deja prodcatorul.
     * @param manufacturer producatorul
     */
    public void addManufacturer(Manufacturer manufacturer) {
        if(this.searchManufacturerByName(manufacturer.getName()) != null){
            throw new DuplicateManufacturerException("Producatorul exista deja in store.");
        }
        this.manufacturers.add(manufacturer);
    }


    /**
     * Adauga un produs nou in lista de produse.
     * Totodata, se verifica daca pretul e pozitiv si produsul nu exista deja in lista.
     * @param product produsul care trebuie adaugat
     */
    public void addProduct(Product product){
        if(product == null){
            return;
        }
        if(product.getPrice() < 0){
            throw new NegativePriceException("Pretul unui produs nu poate fi negativ.");
        }
        if(searchProductByID(product.getUniqueId()) != null){
            throw new DuplicateProductException("Produsul " + product.getUniqueId() + " exista deja in store");
        }
        product.getManufacturer().incrementCountProducts();

        this.products.add(product);
    }


    /**
     * Cauta un produs dupa id
     * @param id id-ul produsului
     * @return produsul gasit
     */
    public Product searchProductByID(String id){
        for(Product product : this.products){
            if(product.getUniqueId().equals(id)){
                return product;
            }
        }
        return null;
    }

    /**
     * Cauta o moneda dupa simbolul ei
     * @param symbol simbolul monedei
     * @return moneda gasita
     */
    public Currency searchCurrencyBySymbol(String symbol){
        for(Currency currency : this.currencies){
            if(currency.getSymbol().equals(symbol)){
                return currency;
            }
        }
        return null;
    }

    /**
     * Converteste de la o moneda la alta
     * @param price valoarea care trebuie convertita
     * @param initialCurrency moneda initiala
     * @param desiredCurrency moneda dorita
     * @return valoarea finala
     */
    public static double convertCurrency(double price, Currency initialCurrency, Currency desiredCurrency){
        return price * initialCurrency.getParityToEur() / desiredCurrency.getParityToEur();
    }

    /**
     * Cauta un discount in lista de discount-uri
     * @param type tipul discount-ului cautat
     * @param value valoarea discount-ului cautat
     * @return discount-ul gasit
     */
    public Discount searchDiscountByTypeAndValue(DiscountType type, double value){
        for(Discount discount : this.discounts){
            if(discount.getType() == type && discount.getValue() == value){
                return discount;
            }
        }
        return null;
    }
}
