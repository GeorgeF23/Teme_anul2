package com.george.Exceptions;

public class DuplicateManufacturerException extends RuntimeException {
    public DuplicateManufacturerException(String msg){
        super(msg);
    }
}
