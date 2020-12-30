package com.george;

public class Manufacturer {
    private String name;
    private int countProducts;

    public Manufacturer(String name) {
        this(name, 0);
    }

    public Manufacturer(String name, int countProducts) {
        this.name = name;
        this.countProducts = countProducts;
    }

    public String getName() {
        return name;
    }
}
