package com.george.commands;

import com.george.AuctionHouse;
import com.george.Broker;

/**
 * Comanda care afiseaza toti brokerii
 */
public class PrintBrokers implements ICommand{
    private final AuctionHouse auctionHouse;

    /**
     * Creeaza comanda si retine parametrii acesteia in atributele clasei
     *
     * @param auctionHouse casa de licitatii
     */
    public PrintBrokers(AuctionHouse auctionHouse) {
        this.auctionHouse = auctionHouse;
    }

    /**
     * Afiseaza informatiile despre fiecare broker
     */
    @Override
    public void execute() {
        for(Broker broker : this.auctionHouse.getBrokers()){
            System.out.println(broker);
        }
    }

    /**
     * Creeaza un string cu detaliile comenzii
     */
    @Override
    public String toString() {
        return "PrintBrokers";
    }
}
