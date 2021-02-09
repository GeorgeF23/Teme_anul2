package com.george.exceptions;

/**
 * Exceptie care se arunca atunci cand un client incearca sa se alature unei licitatii care a inceput deja
 */
public class AuctionAlreadyStartedException extends RuntimeException {
    public AuctionAlreadyStartedException(String message) {
        super(message);
    }
}
