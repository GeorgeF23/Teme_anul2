package com.george;

/**
 * Clasa ce retine infromatiile despre o licitatie necesare pentru client
 */
public class AuctionInfo {
    private final int auctionId;
    private final Broker broker;
    private final double maxBid;
    private double currentMaxBid;

    /**
     * Creeaza un obiect cu informatiile despre o licitatie necesare clientului
     *
     * @param auctionId id-ul licitatiei
     * @param broker    brokerul asociat
     * @param maxBid    suma maxima pe care clientul e dispus sa o liciteze
     */
    public AuctionInfo(int auctionId, Broker broker, double maxBid) {
        this.auctionId = auctionId;
        this.broker = broker;
        this.maxBid = maxBid;
    }

    /**
     * Getter pentru broker-ul asociat licitatiei
     *
     * @return broker-ul
     */
    public Broker getBroker() {
        return broker;
    }

    /**
     * Getter pentru id-ul licitatiei
     *
     * @return id-ul licitatiei
     */
    public int getAuctionId() {
        return auctionId;
    }

    /**
     * Getter pentru suma maxima pe care clientul e dispus sa o liciteze
     *
     * @return suma maxima
     */
    public double getMaxBid() {
        return maxBid;
    }

    /**
     * Setter pentru suma maxima licitata la momentul actual
     *
     * @param currentMaxBid suma licitata
     */
    public void setCurrentMaxBid(double currentMaxBid) {
        this.currentMaxBid = currentMaxBid;
    }
}
