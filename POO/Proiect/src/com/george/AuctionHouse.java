package com.george;

import com.george.exceptions.AuctionAlreadyStartedException;
import com.george.exceptions.NoBrokersException;
import com.george.exceptions.ProductNotFoundException;
import com.george.products.Product;

import java.util.*;

/**
 * Clasa ce descrie o casa de licitatii
 */
public class AuctionHouse {

    private static final int MAX_STEPS = 5;
    private static final int REQUIRED_PARTICIPANTS_COUNT = 3;


    private static AuctionHouse instance;
    private static final Random randomGenerator = new Random();

    private final List<Product> products;
    private final List<Product> soldProducts;
    private final ArrayList<Client> clients;
    private final ArrayList<Auction> auctions;
    private final ArrayList<Administrator> administrators;
    private final ArrayList<Broker> brokers;

    private final HashMap<Integer, HashMap<Client, Double>> bids;

    private int nextProductId = 0;

    /**
     * Creeaza instanta casei de licitatii si initializeaza listele
     */
    private AuctionHouse() {
        this.products = Collections.synchronizedList(new ArrayList<>());
        this.soldProducts = Collections.synchronizedList(new ArrayList<>());
        this.clients = new ArrayList<>();
        this.auctions = new ArrayList<>();
        this.administrators = new ArrayList<>();
        this.brokers = new ArrayList<>();
        this.bids = new HashMap<>();
    }

    /**
     * Obtine instanta casei de licitatii
     *
     * @return instanta casei de licitatii
     */
    public static AuctionHouse getInstance() {
        if (instance == null) instance = new AuctionHouse();
        return instance;
    }

    /**
     * Returneaza numarul de clienti inregistrati in casa de licitatii
     *
     * @return numarul de clienti
     */
    public int getNoClients() {
        return clients.size();
    }

    /**
     * Returneaza numarul de produse inregistrate in casa de licitatii
     *
     * @return numarul de produse
     */
    public int getNoProducts() {
        return products.size();
    }

    /**
     * Returneaza numarul de administratori ai casei de licitatie
     *
     * @return numarul de administratori
     */
    public int getNoAdministrators() {
        return this.administrators.size();
    }

    /**
     * Returneaza numarul de brokeri din casa de licitatie
     *
     * @return numarul de brokeri
     */
    public int getNoBrokers() {
        return this.brokers.size();
    }

    /**
     * Getter pentru lista de licitatii
     *
     * @return lista de licitatii
     */
    public List<Auction> getAuctions() {
        return this.auctions;
    }

    /**
     * Cauta un client dupa id-ul acestuia
     *
     * @param id id-ul clientului
     * @return clientul gasit / null daca acesta nu exista
     */
    public synchronized Client findClientById(int id) {
        return this.clients.stream()
                .filter(client -> client.getId() == id)
                .findAny()
                .orElse(null);
    }

    /**
     * Cauta un produs dupa id-ul acestuia in lista de produse nevandute
     *
     * @param id id-ul produsului
     * @return produsul gasit / null daca nu exista
     */
    public synchronized Product findProductById(int id) {
        return this.products.stream()
                .filter(product -> product.getId() == id)
                .findAny()
                .orElse(null);
    }

    /**
     * Cauta un administrator dupa id-ul acestuia
     *
     * @param id id-ul adiministratorului
     * @return administratorul gasit / null daca nu exista
     */
    public Administrator findAdministratorById(int id) {
        return this.administrators.stream()
                .filter(employee -> employee.getId() == id)
                .findAny()
                .orElse(null);
    }

    /**
     * Cauta un broker dupa id-ul acestuia
     *
     * @param id id-ul brokerului
     * @return brokerul gasit / null daca nu exista
     */
    public Broker findBrokerById(int id) {
        return this.brokers.stream()
                .filter(employee -> employee.getId() == id)
                .findAny()
                .orElse(null);
    }

    /**
     * Cauta o licitatie dupa id-ul produsului care se vinde
     *
     * @param productId id-ul produsului
     * @return licitatia gasita / null daca nu exista
     */
    public Auction findAuctionByProductId(int productId) {
        return this.auctions.stream()
                .filter(auction -> auction.getProductId() == productId)
                .findAny()
                .orElse(null);
    }

    /**
     * Adauga un client nou in lista de clienti
     *
     * @param client clientul care va fi adaugat
     */
    public void addClient(Client client) {
        this.clients.add(client);
    }

    /**
     * Adauga un produs in lista de produse vandute
     *
     * @param product produsul care va fi adaugat
     */
    public void addSoldProduct(Product product) {
        this.soldProducts.add(product);
    }

    /**
     * Adauga un administrator nou in lista de administratori
     *
     * @param administrator administratorul care va fi adaugat
     */
    public void addAdministrator(Administrator administrator) {
        this.administrators.add(administrator);
    }

    /**
     * Adauga un broker nou in lista de brokerie
     *
     * @param broker brokerul care va fi adaugat
     */
    public void addBroker(Broker broker) {
        this.brokers.add(broker);
    }

    /**
     * Getter pentru lista de produse nevandute
     *
     * @return lista de produse nevandute
     */
    public List<Product> getProducts() {
        return products;
    }

    /**
     * Getter pentru lista de produse vandute
     *
     * @return lista de produse vandute
     */
    public List<Product> getSoldProducts() {
        return this.soldProducts;
    }

    /**
     * Getter pentru lista de clienti
     *
     * @return lista de clienti
     */
    public List<Client> getClients() {
        return this.clients;
    }

    /**
     * Getter pentru lista de brokeri
     *
     * @return lista de brokeri
     */
    public List<Broker> getBrokers() {
        return brokers;
    }

    /**
     * Getter pentru urmatorul id disponibil pentru produsele noi
     *
     * @return id-ul disponibil
     */
    public int getNextProductId() {
        return this.nextProductId;
    }

    /**
     * Incrementeaza urmatorul id disponibil pentru produsele noi
     */
    public void incrementNextProductId() {
        this.nextProductId++;
    }

    /**
     * Metoda care se ocupa de cererile de produse
     *
     * @param productId produsul care se doreste a fi cumparat
     * @param maxBid    pretul maxim pe care e dispus clientul sa il plateasca
     * @return informatiile despre licitatie pentru client
     */
    public AuctionInfo receiveProductRequest(int productId, double maxBid) {

        if (this.brokers.isEmpty()) {
            throw new NoBrokersException("Nu exista brokeri.");
        }

        Product product = findProductById(productId);
        if (product == null) {
            throw new ProductNotFoundException("Produsul nu exista in casa de licitatii.");
        }

        Auction auction = findAuctionByProductId(productId);    // Cauta daca exista deja licitatie pentru produsul cerut
        if (auction == null) {  // Daca nu exista, atunci creeaza una noua
            auction = new Auction(this.auctions.size(), 1, productId, MAX_STEPS, this);
            this.auctions.add(auction);
        } else {    // Daca exista deja, incearca sa il adauge pe client in ea
            if (auction.getThreadReference() != null && auction.getThreadReference().isAlive()) {
                throw new AuctionAlreadyStartedException("Licitatia a inceput deja.");
            }
            auction.incrementNoParticipants();
            if (auction.getNoParticipants() == REQUIRED_PARTICIPANTS_COUNT) {
                System.out.println("Licitatia cu id " + auction.getId() + " pentru produsul cu id " + auction.getProductId() + " incepe.");
                this.announceAuctionStart(auction);
                auction.setThreadReference(new Thread(auction));
                auction.getThreadReference().start();
            }
        }
        return new AuctionInfo(auction.getId(), this.brokers.get(randomGenerator.nextInt(this.brokers.size())), maxBid);
    }

    /**
     * Anunta toti brokerii de startul licitatiei
     *
     * @param auction referinta catre licitatie
     */
    private void announceAuctionStart(Auction auction) {
        for (Broker broker : this.brokers) {
            broker.announceAuctionStart(auction);
        }
    }

    /**
     * Metoda ce se ocupa de bid-urile primite de la brokeri
     *
     * @param auctionId id-ul licitatiei pentru care se primesc bid-urile
     * @param bidsArray bid-urile primite
     */
    public synchronized void receiveBidsForAuction(int auctionId, Map<Client, Double> bidsArray) {
        if (this.bids.get(auctionId) == null) {
            this.bids.put(auctionId, (HashMap<Client, Double>) bidsArray);
        } else {
            this.bids.get(auctionId).putAll(bidsArray);
        }
    }

    /**
     * Returneaza bid-ul maxim pentru licitatia ceruta
     *
     * @param auctionId id-ul licitatiei
     * @return perechea (Client, Bid) cu bid-ul cel mai mare
     */
    public synchronized Map.Entry<Client, Double> computeMaxBidForAuction(int auctionId) {
        return Collections.max(this.bids.get(auctionId).entrySet(), Map.Entry.comparingByValue());
    }

}
