package com.george.products;

/**
 * Clasa abstracta ce descrie un produs
 */
public abstract class Product {
    private int id = -1;
    private String name;
    private double finalPrice = -1;
    private double minimumPrice = -1;
    private int year = -1;

    /**
     * Getter pentru id-ul produsului
     *
     * @return id-ul produsului
     */
    public int getId() {
        return id;
    }

    /**
     * Setter pentru id-ul produsului
     *
     * @param id noul id al produsului
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * Getter pentru numele produsului
     *
     * @return numele produsului
     */
    public String getName() {
        return name;
    }

    /**
     * Setter pentru numele produsului
     *
     * @param name noul nume al produsului
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Setter pentru pretul final al produsului
     *
     * @param finalPrice noul pret final al produsului
     */
    public void setFinalPrice(double finalPrice) {
        this.finalPrice = finalPrice;
    }

    /**
     * Getter pentru pretul minim al produsului
     *
     * @return pretul minim al produsului
     */
    public double getMinimumPrice() {
        return minimumPrice;
    }

    /**
     * Setter pentru pretul minim al produsului
     *
     * @param minimumPrice noul pret minim al produsului
     */
    public void setMinimumPrice(double minimumPrice) {
        this.minimumPrice = minimumPrice;
    }

    /**
     * Getter pentru anul de fabricatie al produsului
     *
     * @return anul de fabricatie al produsului
     */
    public int getYear() {
        return year;
    }

    /**
     * Setter pentru anul de fabricatie al produsului
     *
     * @param year noul an de fabricatie al produsului
     */
    public void setYear(int year) {
        this.year = year;
    }

    /**
     * Creeaza un string cu detaliile produsului
     *
     * @return stringul creat
     */
    @Override
    public String toString() {
        return "id=" + id +
                ", name='" + name + '\'' +
                ", finalPrice=" + finalPrice +
                ", minimumPrice=" + minimumPrice +
                ", year=" + year;
    }
}
