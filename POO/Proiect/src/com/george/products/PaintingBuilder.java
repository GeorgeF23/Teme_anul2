package com.george.products;

/**
 * Clasa care construieste un obiect de tipul: Painting
 */
public class PaintingBuilder {

    private final Painting painting;

    /**
     * Initializeaza produsul care se va crea
     */
    public PaintingBuilder() {
        this.painting = new Painting();
    }

    /**
     * Atribuie id-ul produsului
     */
    public PaintingBuilder withId(int id) {
        this.painting.setId(id);
        return this;
    }

    /**
     * Atribuie numele produsului
     */
    public PaintingBuilder withName(String name) {
        this.painting.setName(name);
        return this;
    }

    /**
     * Atribuie pretul minim al produsului
     */
    public PaintingBuilder withMinimumPrice(Double price) {
        this.painting.setMinimumPrice(price);
        return this;
    }

    /**
     * Atribuie anul de fabricatie al produsului
     */
    public PaintingBuilder withYear(Integer year) {
        this.painting.setYear(year);
        return this;
    }

    /**
     * Atribuie numele autorului picturii
     */
    public PaintingBuilder withAuthorName(String name) {
        this.painting.setAuthorName(name);
        return this;
    }

    /**
     * Atribuie tipul de culoare folosit in pictura
     */
    public PaintingBuilder withColors(String colors) {
        try {
            this.painting.setColors(TIP_CULORI.valueOf(colors));
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
        return this;
    }

    /**
     * Verifica daca toate campurile au fost completate si intoarce produsul creat
     *
     * @return produsul creat
     */
    public Painting build() {
        if (painting.getId() == -1 || painting.getName() == null || painting.getMinimumPrice() == -1 || painting.getYear() == -1
                || painting.getAuthorName() == null || painting.getColors() == null) {
            return null;
        }
        return this.painting;
    }
}
