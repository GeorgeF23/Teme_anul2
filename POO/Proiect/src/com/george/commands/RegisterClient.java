package com.george.commands;

import com.george.*;

/**
 * Comanda care inregistreaza un client nou in casa de licitatii
 */
public class RegisterClient implements ICommand {

    private final AuctionHouse auctionHouse;
    private final Client client;

    /**
     * Creeaza comanda si retine parametrii acesteia in atributele clasei
     * Construieste un client de tip: persoana fizica
     *
     * @param auctionHouse casa de licitatii
     * @param name         numele clientului
     * @param address      adresa clientului
     * @param birthday     data nasterii
     */
    public RegisterClient(AuctionHouse auctionHouse, String name, String address, String birthday) {
        this.auctionHouse = auctionHouse;
        int newClientId = this.auctionHouse.getNoClients();
        this.client = new Individual(newClientId, name, address, birthday);
    }

    /**
     * Creeaza comanda si retine parametrii acesteia in atributele clasei
     * Construieste un client de tip: persoana juridica
     *
     * @param auctionHouse casa de licitatii
     * @param name         numele clientului
     * @param address      adresa clientului
     * @param type         tipul de companie
     * @param assets       capitalul companiei
     */
    public RegisterClient(AuctionHouse auctionHouse, String name, String address, COMPANY_TYPE type, double assets) {
        this.auctionHouse = auctionHouse;
        int newClientId = this.auctionHouse.getNoClients();
        this.client = new Company(newClientId, name, address, type, assets);
    }


    /**
     * Adauga clientul nou creat in lista de clienti din casa de licitatie
     */
    @Override
    public void execute() {
        this.auctionHouse.addClient(this.client);
    }

    /**
     * Creeaza un string cu detaliile comenzii
     */
    @Override
    public String toString() {
        return "RegisterClient (" + this.client.getName() + ")";
    }
}
