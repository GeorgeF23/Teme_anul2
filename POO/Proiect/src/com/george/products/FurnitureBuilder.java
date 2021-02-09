package com.george.products;

/**
 * Clasa care construieste un obiect de tip Furniture
 */
public class FurnitureBuilder {
    private final Furniture furniture;

    /**
     * Initializeaza produsul care se va crea
     */
    public FurnitureBuilder() {
        this.furniture = new Furniture();
    }

    /**
     * Atribuie id-ul produsului
     */
    public FurnitureBuilder withId(int id) {
        this.furniture.setId(id);
        return this;
    }

    /**
     * Atribuie numele produsului
     */
    public FurnitureBuilder withName(String nume) {
        this.furniture.setName(nume);
        return this;
    }

    /**
     * Atribuie pretul minim al produsului
     */
    public FurnitureBuilder withMinimumPrice(double pret) {
        this.furniture.setMinimumPrice(pret);
        return this;
    }

    /**
     * Atribuie anul de fabricatie al produsului
     */
    public FurnitureBuilder withYear(int an) {
        this.furniture.setYear(an);
        return this;
    }

    /**
     * Atribuie tipul mobilei
     */
    public FurnitureBuilder withType(String tip) {
        this.furniture.setType(tip);
        return this;
    }

    /**
     * Atribuie materialul mobilei
     */
    public FurnitureBuilder withMaterial(String material) {
        this.furniture.setMaterial(material);
        return this;
    }

    /**
     * Verifica daca toate campurile au fost completate si intoarce produsul creat
     *
     * @return produsul creat
     */
    public Furniture build() {
        if (furniture.getId() == -1 || furniture.getName() == null || furniture.getMinimumPrice() == -1 || furniture.getYear() == -1
                || furniture.getType() == null || furniture.getMaterial() == null) {
            return null;
        }
        return this.furniture;
    }
}
