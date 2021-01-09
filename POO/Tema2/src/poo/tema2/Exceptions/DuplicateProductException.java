package poo.tema2.Exceptions;

public class DuplicateProductException extends RuntimeException {
    public DuplicateProductException(String message){
        super(message);
    }
}
