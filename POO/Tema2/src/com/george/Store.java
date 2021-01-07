package com.george;

import com.george.Exceptions.DuplicateManufacturerException;
import com.george.Exceptions.DuplicateProductException;
import com.opencsv.CSVReader;
import com.opencsv.exceptions.CsvValidationException;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Store {
    private static Store instance;

    private String name;
    private Currency currentCurrency;
    private ArrayList<Currency> currencies;
    private ArrayList<Product> products;
    private ArrayList<Manufacturer> manufacturers;


    public static Store getInstance() {
        if (instance == null) {
            instance = new Store();
        }
        return instance;
    }

    private Store(){
        this.products = new ArrayList<>();
        this.manufacturers = new ArrayList<>();
    }

    public void readCsv(String filename) throws IOException, CsvValidationException {
        CSVReader reader = new CSVReader(new FileReader(filename));

        String[] nextLine;
        while ((nextLine = reader.readNext()) != null) {
            ProductBuilder productBuilder = new ProductBuilder();
        }
    }

    public void addProduct(Product product) throws DuplicateProductException {
        for(Product p : this.products){
            if(p.getUniqueId().equals(product.getUniqueId())){
                throw new DuplicateProductException("Produsul exista deja in magazin.");
            }
        }
        this.products.add(product);
    }

    public void addManufacturer(Manufacturer manufacturer) throws DuplicateManufacturerException{
        for(Manufacturer m : this.manufacturers){
            if(m.getName().equals(manufacturer.getName())){
                throw new DuplicateManufacturerException("Producatorul exista deja in lista.");
            }
        }
    }
}
