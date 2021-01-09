package poo.tema2.Exceptions;

public class NegativePriceException extends RuntimeException{
    public NegativePriceException(String message){
        super(message);
    }
}
