package poo.tema2.Commands;

import com.opencsv.CSVReader;
import com.opencsv.exceptions.CsvValidationException;
import poo.tema2.*;
import poo.tema2.Exceptions.CurrencyNotFoundException;
import poo.tema2.Exceptions.DuplicateManufacturerException;
import poo.tema2.Exceptions.DuplicateProductException;

import javax.print.attribute.standard.MediaSize;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;


/**
 * Clasa care implementeaza comanda ce citeste fisierul csv si adauga produsele in store
 */
public class LoadCSV implements ICommand {
    private static final int ID = 0;
    private static final int NAME = 1;
    private static final int MANUFACTURER = 2;
    private static final int PRICE = 3;
    private static final int QUANTITY = 4;


    private final Store store;
    private final String filename;

    public LoadCSV(Store store, String filename) {
        this.store = store;
        this.filename = filename;
    }

    /**
     * Converteste pretul primit de la input din string in double, facand conversia monedelor
     *
     * @param priceString pretul primit
     * @return valoarea pretului convertit in double
     */
    private double parsePrice(String priceString) {
        String firstPrice = priceString.split("-")[0].trim();   // Daca pretul e un interval atunci pastrez doar primul pret
        String[] priceSplit = firstPrice.split("(?<=\\D)(?=\\d)", 2);   // Separ simbolul monedei de pret
        String symbol = priceSplit[0];
        double value = Double.parseDouble(priceSplit[1].replace(",", ""));  // Sterg virgula care delimiteaza cifra miilor de restul cifrelor

        Currency currency = this.store.searchCurrencyBySymbol(symbol);
        if (currency == null) {
            throw new CurrencyNotFoundException("Moneda nu exista in store");
        }

        return Store.convertCurrency(value, currency, this.store.getCurrentCurrency());
    }


    /**
     * Cauta producatorul in store dupa nume.
     * Daca exista deja in store il returneaza, daca nu creaza un producator nou si il returneaza
     *
     * @param name numele producatorului
     * @return producatorul gasit / creat
     */
    private Manufacturer searchOrCreateManufacturer(String name) {
        Manufacturer manufacturer = this.store.searchManufacturerByName(name);
        if (manufacturer != null) {
            return manufacturer;
        }
        manufacturer = new Manufacturer(name);
        this.store.addManufacturer(manufacturer);
        return manufacturer;
    }

    /**
     * Creeaza un produs nou folosind informatiile primite ca parametru
     *
     * @param values informatiile produsului
     * @return produsul nou creat
     */
    private Product createProduct(String[] values) {
        if (values[PRICE].isEmpty()) {
            return null;
        }
        Manufacturer manufacturer = searchOrCreateManufacturer(values[MANUFACTURER]);

        return new ProductBuilder()
                .withUniqueId(values[ID])
                .withName(values[NAME])
                .withManufacturer(manufacturer)
                .withPrice(parsePrice(values[PRICE]))
                .withQuantity(values[QUANTITY].isEmpty() ? 0 : Integer.parseInt(values[QUANTITY].split("")[0]))  // Elimin "new"
                .build();

    }

    @Override
    public void execute() {
        CSVReader reader = null;
        try {
            reader = new CSVReader(new FileReader(this.filename));
            String[] nextLine = reader.readNext(); // Sar peste prima linie
            while ((nextLine = reader.readNext()) != null) {
                if(nextLine.length >= 4){
                    try{
                        this.store.addProduct(createProduct(nextLine));
                    } catch(DuplicateProductException e){
                        System.err.println(e.getMessage());
                    }
                }
            }
        } catch (CsvValidationException | IOException e) {
            e.printStackTrace();
        }
    }
}
