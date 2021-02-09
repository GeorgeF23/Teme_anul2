package com.george.products;

/**
 * Clasa care construieste un obiect de tip Jewel
 */
public class JewelBuilder {
    private final Jewel jewel;

    /**
     * Initializeaza produsul care se va crea
     */
    public JewelBuilder() {
        this.jewel = new Jewel();
    }

    /**
     * Atribuie id-ul produsul
     */
    public JewelBuilder withId(int id) {
        this.jewel.setId(id);
        return this;
    }

    /**
     * Atribuie numele produsul
     */
    public JewelBuilder withName(String nume) {
        this.jewel.setName(nume);
        return this;
    }

    /**
     * Atribuie pretul minim al produsului
     */
    public JewelBuilder withMinimumPrice(double pret) {
        this.jewel.setMinimumPrice(pret);
        return this;
    }

    /**
     * Atribuie anul de fabricatie al produsului
     */
    public JewelBuilder withYear(int an) {
        this.jewel.setYear(an);
        return this;
    }

    /**
     * Atribuie materialul bijuteriei
     */
    public JewelBuilder withMaterial(String material) {
        this.jewel.setMaterial(material);
        return this;
    }

    /**
     * Atribuie proprietatea de piatra pretioasa
     */
    public JewelBuilder isGem(boolean piatraPretioasa) {
        this.jewel.setGem(piatraPretioasa);
        return this;
    }

    /**
     * Verifica daca toate campurile au fost completate si intoarce produsul creat
     *
     * @return produsul creat
     */
    public Jewel build() {
        if (jewel.getId() == -1 || jewel.getName() == null || jewel.getMinimumPrice() == -1 || jewel.getYear() == -1
                || jewel.getMaterial() == null) {
            return null;
        }
        return this.jewel;
    }
}
