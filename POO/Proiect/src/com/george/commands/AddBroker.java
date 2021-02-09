package com.george.commands;

import com.george.AuctionHouse;
import com.george.Broker;

/**
 * Comanda care adauga un nou broker
 */
public class AddBroker implements ICommand {

    private final AuctionHouse auctionHouse;

    /**
     * Creeaza comanda si retine parametrii acesteia in atributele clasei
     *
     * @param auctionHouse casa de licitatii careia ii adauga broker
     */
    public AddBroker(AuctionHouse auctionHouse) {
        this.auctionHouse = auctionHouse;
    }

    /**
     * Creeaza un nou broker si il adauga in lista
     */
    @Override
    public void execute() {
        Broker newBroker = new Broker(this.auctionHouse.getNoBrokers());
        this.auctionHouse.addBroker(newBroker);
    }

    /**
     * Creaza un string cu detaliile comenzii
     */
    @Override
    public String toString() {
        return "AddBroker: Adaug inca un broker";
    }
}
