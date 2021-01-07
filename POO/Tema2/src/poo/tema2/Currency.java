package poo.tema2;

public class Currency {
    private String name;
    private String symbol;
    private double parityToEur;

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
