package poo.tema2.Exceptions;

public class DuplicateCurrencyException extends RuntimeException{
    public DuplicateCurrencyException(String message){
        super(message);
    }
}
