package com.george.products;

/**
 * Enum pentru tipul de culori pe care il poate avea o pictura
 */
enum TIP_CULORI {
    ULEI,
    TEMPERA,
    ACRILIC
}

/**
 * Clasa ce descrie un produs de tipul: Pictura
 */
public class Painting extends Product {
    private String authorName;
    private TIP_CULORI colors;

    /**
     * Getter pentru numele autorului
     *
     * @return numele autorului
     */
    public String getAuthorName() {
        return authorName;
    }

    /**
     * Setter pentru numele autorului
     *
     * @param authorName noul nume al autorului
     */
    public void setAuthorName(String authorName) {
        this.authorName = authorName;
    }

    /**
     * Getter pentru tipul de culoare
     *
     * @return tipul de culoare
     */
    public TIP_CULORI getColors() {
        return colors;
    }

    /**
     * Setter pentru tipul de culoare
     *
     * @param colors noul tip de culoare
     */
    public void setColors(TIP_CULORI colors) {
        this.colors = colors;
    }

    /**
     * Creeaza un string cu detalii despre produs
     *
     * @return stringul creat
     */
    @Override
    public String toString() {
        return super.toString() +
                " type=Painting " +
                "authorName='" + authorName + '\'' +
                ", colors=" + colors;
    }
}
