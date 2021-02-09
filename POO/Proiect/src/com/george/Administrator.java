package com.george;

import com.george.products.Product;

/**
 * Clasa ce descrie un angajat de tipul: Administrator
 */
public class Administrator implements Employee {
    private final int id;
    private final String name;

    /**
     * Creeaza un administrator nou
     *
     * @param id   id-ul administratorului
     * @param name numele administratorului
     */
    public Administrator(int id, String name) {
        this.id = id;
        this.name = name;
    }

    /**
     * Metoda prin care un administrator adauga un produs nou in casa de licitatii
     *
     * @param auctionHouse casa de licitatii in care adauga produsul
     * @param product      produsul pe care il adauga
     */
    public synchronized void addProduct(AuctionHouse auctionHouse, Product product) {
        auctionHouse.getProducts().add(product);
    }

    /**
     * Getter pentru id-ul administratorului
     *
     * @return id-ul administratorului
     */
    public int getId() {
        return id;
    }

    /**
     * Getter pentru numele administratorului
     *
     * @return numele administratorului
     */
    public String getName() {
        return name;
    }
}
