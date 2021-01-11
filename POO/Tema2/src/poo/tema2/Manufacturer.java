package poo.tema2;

/**
 * Clasa ce descrie un producator
 */
public class Manufacturer {
    private final String name;
    private int countProducts;

    /**
     * Creeaza un producator nou cu 0 produse
     * @param name numele prodcatorului
     */
    public Manufacturer(String name){
        this(name, 0);
    }

    /**
     * Creeaza un producator
     * @param name numele prodcatorului
     * @param countProducts numarul de produse ale producatorului
     */
    public Manufacturer(String name, int countProducts){
        this.name = name;
        this.countProducts = countProducts;
    }

    /**
     * Getter pentru nummele prodcatorului
     * @return numele producatorului
     */
    public String getName() {
        return name;
    }

    /**
     * Getter pentru numarul de produse ale prodcatorului
     * @return numarul de produse
     */
    public int getCountProducts() {
        return countProducts;
    }

    /**
     * Incrementeaza numarul de produse al prodcatorului
     */
    public void incrementCountProducts(){
        this.countProducts++;
    }
}
