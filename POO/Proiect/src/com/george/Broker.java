package com.george;

import com.george.products.Product;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * Clasa ce descrie un broker
 */
public class Broker implements Employee {
    private final int id;
    private double commissions;
    private final CopyOnWriteArrayList<Client> clients;

    /**
     * Creeaza un broker nou
     *
     * @param id id-ul broker-ului
     */
    public Broker(int id) {
        this.id = id;
        this.clients = new CopyOnWriteArrayList<>();
    }

    /**
     * Getter pentru id-ul brokerului
     *
     * @return id-ul
     */
    @Override
    public int getId() {
        return this.id;
    }

    /**
     * Adauga un client nou in lista de clienti a broker-ului
     *
     * @param client clientul nou
     */
    public void addClient(Client client) {
        if (!this.clients.contains(client)) {
            this.clients.add(client);
        }
    }

    /**
     * Metoda ce se ocupa de primirea notificarii de inceput de licitatie
     * Aici broker-ul este anuntat ca o licitatie a inceput
     *
     * @param auction licitatia
     */
    public void announceAuctionStart(Auction auction) {
        System.out.printf("Brokerul cu id %d a fost anuntat de startul licitatiei %d%n", this.id, auction.getId());
    }

    /**
     * Cauta toti clientii broker-ului care sunt inscrisi la o licitatie
     *
     * @param auctionId id-ul licitatiei
     * @return lista de clienti inscrisi in licitatie
     */
    public synchronized List<Client> getClientsInAuction(int auctionId) {
        ArrayList<Client> clientsInAuction = new ArrayList<>();
        for (Client client : this.clients) {
            if (client.findAuctionInfoByAuctionId(auctionId) != null) {
                clientsInAuction.add(client);
            }
        }
        return clientsInAuction;
    }

    /**
     * Metoda prin care broker-ul le cere clientilor suma pe care doresc sa o liciteze
     *
     * @param auctionId id-ul licitatiei
     * @return sumele licitate de fiecare client
     */
    public synchronized Map<Client, Double> getClientsBidsInAuction(int auctionId) {
        HashMap<Client, Double> bidsArray = new HashMap<>();
        for (Client client : this.getClientsInAuction(auctionId)) {
            bidsArray.put(client, client.getBidForAuction(auctionId));
        }
        return bidsArray;
    }

    /**
     * Metoda prin care broker-ul trimite casei de licitatii sumele licitate de fiecare client pentru o anumita licitatie
     *
     * @param auctionHouse casa de licitatii
     * @param bidsArray    sumele licitate de clienti
     * @param auctionId    id-ul licitatiei
     */
    public synchronized void sendBids(AuctionHouse auctionHouse, Map<Client, Double> bidsArray, int auctionId) {
        auctionHouse.receiveBidsForAuction(auctionId, bidsArray);
    }

    /**
     * Metoda prin care broker-ul le trimite clientilor sai suma maxima licitata la un anumit pas
     *
     * @param auctionId id-ul licitatiei
     * @param maxBid    suma maxima licitata
     */
    public synchronized void sendMaxBidToClientsInAuction(int auctionId, double maxBid) {
        for (Client client : this.getClientsInAuction(auctionId)) {
            client.receiveMaxBid(auctionId, maxBid);
        }
    }

    /**
     * Metoda prin care un broker sterge produsul vandut la licitatie
     * Produsul vandut este adaugat in lista de produse vandute
     *
     * @param auctionHouse casa de licitatii
     * @param productId    id-ul produsului
     */
    public synchronized void removeProduct(AuctionHouse auctionHouse, int productId) {
        Product soldProduct = auctionHouse.findProductById(productId);
        auctionHouse.addSoldProduct(soldProduct);
        auctionHouse.getProducts().removeIf(product -> product.getId() == productId);
        System.out.println("Brokerul cu id " + this.id + " sterge produsul cu id " + productId + ". Produse ramase: " + auctionHouse.getNoProducts() + ".");
    }

    /**
     * Metoda prin care brokerul isi anunta clientii de sfarsitul licitatiei
     *
     * @param auction licitatia terminata
     */
    public void notifyAuctionEnd(Auction auction) {
        for (Client client : this.getClientsInAuction(auction.getId())) {
            client.receiveAuctionEndNotification(auction.getId());
        }
    }

    /**
     * Metoda prin care brokerul isi retine comisionul pentru vanzarea produsului
     *
     * @param winningClient clientul castigator
     * @param winningSum    suma platita pentru produs
     */
    public void chargeCommision(Client winningClient, double winningSum) {
        if (winningClient instanceof Individual) {
            if (winningClient.getNoParticipations() < 5) {
                this.commissions += 0.2 * winningSum;
            } else {
                this.commissions += 0.15 * winningSum;
            }
        } else if (winningClient instanceof Company) {
            if (winningClient.getNoParticipations() < 25) {
                this.commissions += 0.25 * winningSum;
            } else {
                this.commissions += 0.1 * winningSum;
            }
        }
    }

    /**
     * Metoda prin care brokerul elimina clientii dintr-o licitatie terminata si isi sterge din lista sa clientii care nu ii mai apartin
     *
     * @param auctionId id-ul licitatiei
     */
    public void removeClientsFromAuction(int auctionId) {
        for (Client client : this.clients) {
            client.getAuctionsJoined().removeIf(auctionInfo -> auctionInfo.getAuctionId() == auctionId);

            boolean isStillClient = false; // Retine daca clientul mai este intr-o licitatie cu acest broker
            for (AuctionInfo auctionInfo : client.getAuctionsJoined()) {
                if (auctionInfo.getBroker() == this) {
                    isStillClient = true;
                    break;
                }
            }

            if (!isStillClient) {
                this.clients.remove(client);
            }
        }
    }

    /**
     * Creeaza un string cu informatiile broker-ului
     *
     * @return string-ul creat
     */
    @Override
    public String toString() {
        return String.format("Broker cu id %d si %f comisioane.", this.id, this.commissions);
    }
}
