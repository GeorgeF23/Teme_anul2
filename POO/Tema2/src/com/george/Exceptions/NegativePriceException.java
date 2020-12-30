package com.george.Exceptions;

public class NegativePriceException extends RuntimeException {
    public NegativePriceException(String msg){
        super(msg);
    }
}
