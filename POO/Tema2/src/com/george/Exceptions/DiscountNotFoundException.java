package com.george.Exceptions;

public class DiscountNotFoundException extends RuntimeException {
    public DiscountNotFoundException(String msg){
        super(msg);
    }
}
