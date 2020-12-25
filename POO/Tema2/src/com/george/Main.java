package com.george;

import com.opencsv.exceptions.CsvValidationException;

import java.io.IOException;

public class Main {

    public static void main(String[] args) {
	    Store store = Store.getInstance();
	    String csvFileName = "amazon_co-ecommerce_sample.csv";

        try {
            store.readCsv(csvFileName);
        } catch (Exception e) {
            System.out.println("Eroare la citirea fisierului"); // TODO: better exception handling
        }
    }
}
