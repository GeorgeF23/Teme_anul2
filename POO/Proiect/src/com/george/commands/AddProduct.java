package com.george.commands;

import com.george.Administrator;
import com.george.AuctionHouse;
import com.george.products.Product;

/**
 * Comanda care adauga un produs nou
 */
public class AddProduct implements ICommand {

    private final AuctionHouse auctionHouse;
    private final Administrator administrator;
    private final Product product;

    /**
     * Creeaza comanda si retine parametrii acesteia in atributele clasei
     *
     * @param auctionHouse    casa de licitatii in care adauga produsul
     * @param administratorId id-ul administratorului care adauga produsul
     * @param product         produsul care va fi adaugat
     */
    public AddProduct(AuctionHouse auctionHouse, int administratorId, Product product) {
        this.auctionHouse = auctionHouse;
        this.administrator = auctionHouse.findAdministratorById(administratorId);
        this.product = product;
    }

    /**
     * Adauga un produs nou in lista de produse din casa de licitatii
     */
    @Override
    public void execute() {
        if (product != null) {
            this.product.setId(auctionHouse.getNextProductId());    // Ii seteaza id-ul, folosind tehnica de Auto Increment
            auctionHouse.incrementNextProductId();
            this.administrator.addProduct(auctionHouse, product);
        }
    }

    /**
     * Creeaza un string cu detaliile comenzii
     */
    @Override
    public String toString() {
        return String.format("addProduct: Administratorul %s(%d) a adaugat produsul %s", this.administrator.getName(), this.administrator.getId(), this.product);
    }
}
