package com.george.exceptions;

/**
 * Exceptie care se arunca atunci cand se cauta un produs, dar acesta nu exista
 */
public class ProductNotFoundException extends RuntimeException {
    public ProductNotFoundException(String message) {
        super(message);
    }
}
