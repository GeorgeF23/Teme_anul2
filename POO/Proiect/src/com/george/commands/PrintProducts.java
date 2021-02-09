package com.george.commands;

import com.george.AuctionHouse;
import com.george.products.Product;

/**
 * Comanda care afiseaza informatiile fiecarui produs
 */
public class PrintProducts implements ICommand {
    private final AuctionHouse auctionHouse;

    /**
     * Creeaza comanda si retine parametrii acesteia in atributele clasei
     *
     * @param auctionHouse casa de licitatii
     */
    public PrintProducts(AuctionHouse auctionHouse) {
        this.auctionHouse = auctionHouse;
    }

    /**
     * Afiseaza detaliile despre produsele care nu sunt inca vandute, dar si despre cele care s-au vandut deja
     */
    @Override
    public void execute() {
        for (Product product : this.auctionHouse.getProducts()) {
            System.out.println(product);
        }

        for (Product product : this.auctionHouse.getSoldProducts()) {
            System.out.println(product);
        }
    }

    /**
     * Creeaza un string cu detaiile comenzii
     */
    @Override
    public String toString() {
        return "PrintProducts";
    }
}
