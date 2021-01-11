package poo.tema2;

/**
 * Clasa care reprezinta o moneda
 */
public class Currency {
    private final String name;
    private final String symbol;
    private double parityToEur;

    /**
     * Creaza o moneda noua
     * @param name numele monedei
     * @param symbol simbolul monedei
     * @param parityToEur paritatea monedei la euro ( valoare_euro = valoare_moneda * parityToEuro )
     */
    public Currency(String name, String symbol, double parityToEur){
        this.name = name;
        this.symbol = symbol;
        this.parityToEur = parityToEur;
    }

    /**
     * Getter pentru numele monedei
     * @return numele monedei
     */
    public String getName() {
        return name;
    }

    /**
     * Getter pentru simbolul monedei
     * @return simbolul monedei
     */
    public String getSymbol() {
        return symbol;
    }

    /**
     * Getter pentru paritatea la euro
     * @return paritatea la euri
     */
    public double getParityToEur() {
        return parityToEur;
    }

    /**
     * Setter pentru paritatea la euro
     * @param parityToEur paritatea la euro noua
     */
    public void setParityToEur(double parityToEur) {
        this.parityToEur = parityToEur;
    }
}
