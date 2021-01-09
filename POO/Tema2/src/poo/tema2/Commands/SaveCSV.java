package poo.tema2.Commands;

import com.opencsv.CSVWriter;
import poo.tema2.Product;
import poo.tema2.Store;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;


/**
 * Clasa care implementeaza comanda de salvare a tuturor produselor intr-un fisier csv
 */
public class SaveCSV implements ICommand{

    private final static String[] headers = {"unique_id", "product_name", "manufacturer", "price", "quantity"};

    private final Store store;
    private final String outputFileName;

    public SaveCSV(Store store, String outputFileName) {
        this.store = store;
        this.outputFileName = outputFileName;
    }

    /**
     * Converteste lista de produse din store intr-un ArrayList ce contine in fiecare
     * camp toate informatiile ce trebuie trecute in fisierul csv
     * @return ArrayList-ul cu informatiile produselor
     */
    private ArrayList<String[]> getProductsInfo(){
        ArrayList<String[]> productsInfo = new ArrayList<>();
        for(Product product : this.store.getProducts()){
            productsInfo.add(new String[]{
                    product.getUniqueId(),
                    product.getName(),
                    product.getManufacturer().getName(),
                    this.store.getCurrentCurrency().getSymbol() + Double.toString(product.getPrice()),
                    Integer.toString(product.getQuantity()) + '\u00A0'  // Adaug nbsp
            });
        }
        return productsInfo;
    }

    @Override
    public void execute() {
        try{
            CSVWriter csvWriter = new CSVWriter(
                    new FileWriter(this.outputFileName),
                    CSVWriter.DEFAULT_SEPARATOR,
                    CSVWriter.NO_QUOTE_CHARACTER,
                    CSVWriter.DEFAULT_ESCAPE_CHARACTER,
                    CSVWriter.DEFAULT_LINE_END);

            csvWriter.writeNext(SaveCSV.headers);   // Scriu header-ele in fisier
            csvWriter.writeAll(this.getProductsInfo()); // Scriu informatiile despre produse
            csvWriter.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
