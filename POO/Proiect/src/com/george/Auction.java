package com.george;

import com.george.products.Product;

import java.io.IOException;
import java.io.PrintStream;
import java.util.Map;
import java.util.Objects;

/**
 * Clasa care descrie si executa pe un thread separat o licitatie
 */
public class Auction implements Runnable {
    private final int id;
    private int noParticipants;
    private final int productId;
    private final int maxSteps;
    private Thread threadReference;
    private final AuctionHouse auctionHouse;

    /**
     * Creeaza o licitatie noua cu atributele ei date ca parametru
     *
     * @param id             id-ul licitatiei
     * @param noParticipants numarul de participanti la licitatie
     * @param productId      id-ul produsului care se liciteaza
     * @param maxSteps       numarul maxim de pasi
     * @param auctionHouse   casa de licitatii unde se face licitatia
     */
    public Auction(int id, int noParticipants, int productId, int maxSteps, AuctionHouse auctionHouse) {
        this.id = id;
        this.noParticipants = noParticipants;
        this.productId = productId;
        this.maxSteps = maxSteps;
        this.auctionHouse = auctionHouse;
    }

    /**
     * Getter pentru id-ul produsului licitat
     *
     * @return id-ul produsului
     */
    public int getProductId() {
        return productId;
    }

    /**
     * Incrementeaza numarul de participanti la licitatie
     */
    public void incrementNoParticipants() {
        this.noParticipants++;
    }

    /**
     * Getter pentru numarul de participanti
     *
     * @return numarul de participanti
     */
    public int getNoParticipants() {
        return noParticipants;
    }

    /**
     * Getter pentru referinta thread-ului pe care se executa licitatia
     *
     * @return referinta thread-ului
     */
    public Thread getThreadReference() {
        return threadReference;
    }

    /**
     * Setter pentru referinta thread-ului pe care se executa licitatia
     *
     * @param threadReference noua referinta a thread-ului
     */
    public void setThreadReference(Thread threadReference) {
        this.threadReference = threadReference;
    }

    /**
     * Getter pentru id-ul licitatiei
     *
     * @return id-ul licitatiei
     */
    public int getId() {
        return this.id;
    }

    /**
     * Metoda care executa licitatia pe un thread separat
     */
    @Override
    public void run() {
        try (PrintStream logger = new PrintStream(String.format("logs/auction_logs/auction%d.txt", this.id))) {
            logger.printf("A inceput licitatia cu id %d pentru produsul cu id %d%n", this.id, this.productId);

            Client winningClient = null;    // Clientul care castiga licitatia in final
            double winningSum = -1;     // Suma maxima care s-a licitat

            for (int i = 0; i < this.maxSteps; i++) {
                Map<Client, Double> bids;

                for (Broker broker : this.auctionHouse.getBrokers()) {
                    bids = broker.getClientsBidsInAuction(this.id); // Fiecare broker cere suma licitata de la fiecare client al lui care participa la licitatia curenta
                    broker.sendBids(this.auctionHouse, bids, this.id);  // Fiecare broker trimite sumele primite le casa de licitatii
                }
                Map.Entry<Client, Double> currentStepMaxBid = auctionHouse.computeMaxBidForAuction(this.id);    // Suma maxima licitata la pasul curent, impreuna cu clientul

                if (winningClient == null || currentStepMaxBid.getValue() > winningSum ||
                        (currentStepMaxBid.getValue() == winningSum && currentStepMaxBid.getKey().getNoWins() > winningClient.getNoWins())) {
                    winningClient = currentStepMaxBid.getKey();
                    winningSum = currentStepMaxBid.getValue();
                }

                logger.printf("La pasul %d s-a licitat maxim: %s -> %f%n", i + 1, currentStepMaxBid.getKey(), currentStepMaxBid.getValue());
                logger.printf("Primul participant este: %s -> %f%n", winningClient, winningSum);

                for (Broker broker : this.auctionHouse.getBrokers()) {
                    broker.sendMaxBidToClientsInAuction(this.id, currentStepMaxBid.getValue()); // Notifica clientii de suma maxima licitata la pasul curent
                }
                Thread.sleep(100);
            }

            Product product = auctionHouse.findProductById(this.productId);
            if (winningSum < product.getMinimumPrice()) {
                logger.println("Nu s-a atins suma minima pentru produs");
            } else {
                logger.printf("Clientul %s a castigat licitatia cu suma %f%n", winningClient, winningSum);
                Objects.requireNonNull(winningClient).incrementNoWins();

                auctionHouse.findProductById(this.productId).setFinalPrice(winningSum); // Seteaza pretul final produsului

                Broker winningClientBroker = winningClient.findAuctionInfoByAuctionId(this.id).getBroker();
                winningClientBroker.removeProduct(auctionHouse, this.productId);    // Brokerul sterge produsul din lista
                winningClientBroker.chargeCommision(winningClient, winningSum);     // Brokerul isi incaseaza comisionul

            }
            for (Broker broker : this.auctionHouse.getBrokers()) {
                broker.notifyAuctionEnd(this);  // Brokerii notifica clientii de sfarsitul licitatiei
                broker.removeClientsFromAuction(this.id);   // Brokerul sterge din lista de clienti pe cei din licitatia curenta
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}
