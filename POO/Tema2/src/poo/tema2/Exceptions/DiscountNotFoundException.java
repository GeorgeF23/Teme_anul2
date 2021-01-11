package poo.tema2.Exceptions;

public class DiscountNotFoundException extends RuntimeException {
    public DiscountNotFoundException(String message){
        super(message);
    }
}
