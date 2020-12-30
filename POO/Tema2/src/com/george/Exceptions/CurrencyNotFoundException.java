package com.george.Exceptions;

public class CurrencyNotFoundException extends RuntimeException{
    public CurrencyNotFoundException(String msg){
        super(msg);
    }
}
