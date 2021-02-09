package com.george.products;

/**
 * Clasa ce descrie un produs de tipul: Mobila
 */
public class Furniture extends Product {
    private String type;
    private String material;

    /**
     * Getter pentru tipul mobilei
     *
     * @return tipul mobilei
     */
    public String getType() {
        return type;
    }

    /**
     * Setter pentru tipul mobilei
     *
     * @param type tipul mobilei
     */
    public void setType(String type) {
        this.type = type;
    }

    /**
     * Getter pentru materialul din care e confectionata mobila
     *
     * @return materialul din care e confectionata mobila
     */
    public String getMaterial() {
        return material;
    }

    /**
     * Setter pentu materialul din care e confectionata mobila
     *
     * @param material materialul din care e confectionata mobila
     */
    public void setMaterial(String material) {
        this.material = material;
    }

    /**
     * Creeaza un string cu detaliile despre mobila
     */
    @Override
    public String toString() {
        return super.toString() +
                " type=Furniture " +
                "furniture type='" + type + '\'' +
                ", material='" + material + '\'';
    }
}
