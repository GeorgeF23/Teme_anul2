package poo.tema2.Commands;

import com.opencsv.CSVWriter;
import poo.tema2.Product;
import poo.tema2.Store;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class SaveCSV implements ICommand{

    private final static String[] headers = {"unique_id", "product_name", "manufacturer", "price", "quantity"};

    private Store store;
    private String outputFileName;

    public SaveCSV(Store store, String outputFileName) {
        this.store = store;
        this.outputFileName = outputFileName;
    }

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

            csvWriter.writeNext(SaveCSV.headers);
            csvWriter.writeAll(this.getProductsInfo());
            csvWriter.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
