package com.george.exceptions;

/**
 * Exceptie care se arunca atunci cand se cauta un client, dar acesta nu exista
 */
public class ClientNotFoundException extends RuntimeException {
    public ClientNotFoundException(String message) {
        super(message);
    }
}
