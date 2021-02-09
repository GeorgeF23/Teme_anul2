package com.george.exceptions;

/**
 * Exceptie care se arunca atunci cand nu exista brokeri disponibili
 */
public class NoBrokersException extends RuntimeException {
    public NoBrokersException(String message) {
        super(message);
    }
}
