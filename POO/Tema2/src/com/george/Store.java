package com.george;

public class Store {
    private static Store instance;

    private String name;
    private Currency currency;
    private Product[] products;
    private Manufacturer[] manufacturers;


    public static Store getInstance() {
        if (instance == null) {
            instance = new Store();
        }
        return instance;
    }
}
