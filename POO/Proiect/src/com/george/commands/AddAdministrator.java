package com.george.commands;

import com.george.Administrator;
import com.george.AuctionHouse;

/**
 * Comanda care adauga un administrator nou
 */
public class AddAdministrator implements ICommand {

    private final AuctionHouse auctionHouse;
    private final String name;

    /**
     * Creeaza comanda si retine parametrii acesteia in atributele clasei
     *
     * @param auctionHouse casa de licitatii careia ii adauga administratorul
     * @param name         numele administratorului
     */
    public AddAdministrator(AuctionHouse auctionHouse, String name) {
        this.auctionHouse = auctionHouse;
        this.name = name;
    }

    /**
     * Creeaza un nou administrator si il adauga in lista
     */
    @Override
    public void execute() {
        Administrator administrator = new Administrator(this.auctionHouse.getNoAdministrators(), name);
        this.auctionHouse.addAdministrator(administrator);
    }

    /**
     * Creeaza un string cu detaliile comenzii
     */
    @Override
    public String toString() {
        return String.format("AddAdministrator: Adaug administratorul %s", this.name);
    }
}
