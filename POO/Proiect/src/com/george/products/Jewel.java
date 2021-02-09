package com.george.products;

/**
 * Clasa ce descrie un produs de tipul: Bijuterie
 */
public class Jewel extends Product {
    private String material;
    private boolean gem;

    /**
     * Getter pentru materialul din care e confectionata bijuteria
     *
     * @return materialul
     */
    public String getMaterial() {
        return material;
    }

    /**
     * Setter pentru materialul din care e confectionata bijuteria
     *
     * @param material valoarea noua pentru materialul din care e confectionata bijuteria
     */
    public void setMaterial(String material) {
        this.material = material;
    }

    /**
     * Setter pentru proprietatea de piatra pretios
     *
     * @param gem true/false daca e piatra pretioasa
     */
    public void setGem(boolean gem) {
        this.gem = gem;
    }

    /**
     * Creeaza un string cu detaliile despre bijuterie
     *
     * @return string-ul creat
     */
    @Override
    public String toString() {
        return super.toString() +
                " type=Jewel " +
                "material='" + material + '\'' +
                ", gem=" + gem;
    }
}
