package com.george.Exceptions;

public class DuplicateProductException extends RuntimeException {
    public DuplicateProductException(String msg){
        super(msg);
    }
}
