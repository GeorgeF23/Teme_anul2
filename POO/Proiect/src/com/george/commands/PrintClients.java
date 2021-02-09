package com.george.commands;

import com.george.AuctionHouse;
import com.george.Client;

/**
 * Comanda care afiseaza toti clientii inregistrati in casa de licitatie
 */
public class PrintClients implements ICommand {

    private final AuctionHouse auctionHouse;

    /**
     * Creeaza comanda si retine parametrii acesteia in atributele clasei
     *
     * @param auctionHouse casa de licitatii
     */
    public PrintClients(AuctionHouse auctionHouse) {
        this.auctionHouse = auctionHouse;
    }

    /**
     * Afiseaza informatiile despre fiecare client din casa de licitatie
     */
    @Override
    public void execute() {
        for (Client client : this.auctionHouse.getClients()) {
            System.out.println(client.convertClientInfoToString());
        }
    }

    /**
     * Creeaza un string cu detaliile comenzii
     */
    @Override
    public String toString() {
        return "PrintClients";
    }
}
