package com.george;

import java.util.ArrayList;
import java.util.List;

/**
 * Clasa abstracta ce descrie un client
 */
public abstract class Client {
    private final int id;
    private final String name;
    private final String address;
    private int noParticipations;
    private int noWins;

    private final ArrayList<AuctionInfo> auctionsJoined;

    /**
     * Creeaza un client nou
     *
     * @param id      id-ul clientului
     * @param name    numele clientului
     * @param address adresa clientului
     */
    protected Client(int id, String name, String address) {
        this.id = id;
        this.name = name;
        this.address = address;
        this.noParticipations = 0;
        this.noWins = 0;

        this.auctionsJoined = new ArrayList<>();
    }

    /**
     * Getter pentru id-ul clientului
     *
     * @return id-ul clientului
     */
    public int getId() {
        return id;
    }

    /**
     * Getter pentru numele clientului
     *
     * @return numele clientului
     */
    public String getName() {
        return name;
    }

    /**
     * Getter pentru numarul de licitatii la care a participat clientul
     *
     * @return numarul de participari
     */
    public int getNoParticipations() {
        return noParticipations;
    }

    /**
     * Metoda care incrementeaza numarul de participari al clientului
     */
    public void incrementNoParticipations() {
        this.noParticipations++;
    }

    /**
     * Getter pentru numarul de castiguri ale clientului
     *
     * @return numarul de castiguri
     */
    public int getNoWins() {
        return noWins;
    }

    /**
     * Metoda care incrementeaza numarul de castiguri ale clientului
     */
    public void incrementNoWins() {
        this.noWins++;
    }

    /**
     * Getter pentru lista de informatii despre licitatiile la care e inscris clientul
     *
     * @return lista de licitatii
     */
    public List<AuctionInfo> getAuctionsJoined() {
        return this.auctionsJoined;
    }

    public void viewProducts(AuctionHouse auctionHouse) {
        System.out.printf("Clientul %s a cerut sa vada produsele.%n", this.id);
    }

    /**
     * Cauta informatiile despre o licitatie dupa id-ul licitatiei
     *
     * @param auctionId id-ul licitatiei
     * @return informatiile despre licitatie
     */
    public synchronized AuctionInfo findAuctionInfoByAuctionId(int auctionId) {
        return this.auctionsJoined.stream()
                .filter(auctionInfo -> auctionInfo.getAuctionId() == auctionId)
                .findAny()
                .orElse(null);
    }

    /**
     * Metoda prin care un client cere sa participe la o licitatie pentru un produs
     *
     * @param auctionHouse casa de licitatii
     * @param productId    id-ul produsului
     * @param maxBid       suma maxima pe care e dispus sa o liciteze
     */
    public void askForProduct(AuctionHouse auctionHouse, int productId, double maxBid) {
        AuctionInfo auctionInfo = auctionHouse.receiveProductRequest(productId, maxBid);
        auctionInfo.getBroker().addClient(this);
        this.auctionsJoined.add(auctionInfo);
        this.incrementNoParticipations();
    }

    /**
     * Calculeaza suma pe care clientul vrea sa o liciteze la o anumita licitatie
     *
     * @param auctionId id-ul licitatiei
     * @return suma licitata
     */
    public double getBidForAuction(int auctionId) {
        AuctionInfo auctionInfo = this.findAuctionInfoByAuctionId(auctionId);
        if (auctionInfo == null) {
            System.err.println("getBidForAuction: invalid auctionId");
            return -1;
        }
        double maxBid = auctionInfo.getMaxBid();
        return Math.random() * maxBid;
    }

    /**
     * Metoda prin care clientul primeste de la broker suma maxima licitata la o anumita licitatie
     *
     * @param auctionId id-ul licitatiei
     * @param maxBid    suma maxima licitata
     */
    public void receiveMaxBid(int auctionId, double maxBid) {
        AuctionInfo auctionInfo = this.findAuctionInfoByAuctionId(auctionId);
        if (auctionInfo == null) {
            System.err.println("getBidForAuction: invalid auctionId");
            return;
        }
        auctionInfo.setCurrentMaxBid(maxBid);
    }

    /**
     * Metoda prin care clientul este anuntat de broker ca licitatia s-a incheiat
     *
     * @param auctionId id-ul licitatiei incheiate
     */
    public void receiveAuctionEndNotification(int auctionId) {
        System.out.printf("Clientul %s a fost notificat de sfarsitul licitatiei %d%n", this.name, auctionId);
    }

    /**
     * Metoda abstracta care returneaza un string cu informatiile despre client.
     * Ea este definita in clasele Individual si Company
     *
     * @return string cu informatiile despre client
     */
    public abstract String convertClientInfoToString();

    /**
     * Creeaza un string cu informatiile despre client
     *
     * @return string-ul creat
     */
    public String toString() {
        return String.format("[%d] %s", this.id, this.name);
    }
}
