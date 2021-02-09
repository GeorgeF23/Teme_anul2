package com.george.commands;

import com.george.AuctionHouse;
import com.george.Client;
import com.george.exceptions.AuctionAlreadyStartedException;
import com.george.exceptions.ClientNotFoundException;

/**
 * Comanda prin care un client isi arata intentia de a se alatura unei licitatii
 */
public class ClientAskForProduct implements ICommand {

    private final AuctionHouse auctionHouse;
    private final int clientId;
    private final int productId;
    private final double maxBid;

    /**
     * Creeaza comanda si retine parametrii acesteia in atributele clasei
     *
     * @param auctionHouse casa de licitatii unde se afla produsul dorit
     * @param clientId     id-ul clientului care face cererea
     * @param productId    id-ul produsului dorit
     * @param maxBid       suma maxima pe care clientul e dispus sa o liciteze
     */
    public ClientAskForProduct(AuctionHouse auctionHouse, int clientId, int productId, double maxBid) {
        this.auctionHouse = auctionHouse;
        this.clientId = clientId;
        this.productId = productId;
        this.maxBid = maxBid;
    }

    /**
     * Apeleaza functia askForProduct din clasa Client
     */
    @Override
    public void execute() {
        Client client = this.auctionHouse.findClientById(this.clientId);
        if (client == null) {
            throw new ClientNotFoundException("Clientul nu este inregistrat");
        }
        try {
            client.askForProduct(this.auctionHouse, this.productId, this.maxBid);
        } catch (AuctionAlreadyStartedException e) {
            System.err.println(e.getMessage());
        }
    }

    /**
     * Creeaza un string cu detaliile comenzii
     */
    @Override
    public String toString() {
        return String.format("ClientAskForProduct: Clientul %d vrea sa liciteze pentru produsul cu id %d cu bid maxim %f.", this.clientId, this.productId, this.maxBid);
    }
}
