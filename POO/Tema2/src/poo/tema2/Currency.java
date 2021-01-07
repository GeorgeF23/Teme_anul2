package poo.tema2;

/**
 * Class that represents a currency.
 */
public class Currency {
    private String name;
    private String symbol;
    private double parityToEur;

    /**
     * Creates a new currency
     * @param name name of the currency
     * @param symbol symbol of the currency
     * @param parityToEur parity to Euro of the currency
     */
    public Currency(String name, String symbol, double parityToEur){
        this.name = name;
        this.symbol = symbol;
        this.parityToEur = parityToEur;
    }

    public String getName() {
        return name;
    }

    public String getSymbol() {
        return symbol;
    }

    public double getParityToEur() {
        return parityToEur;
    }

    public void setParityToEur(double parityToEur) {
        this.parityToEur = parityToEur;
    }
}
