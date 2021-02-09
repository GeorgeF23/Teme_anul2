package com.george;

/**
 * Clasa ce descrie mai concret un client de tipul persoana juridica
 */
public class Company extends Client {

    private final COMPANY_TYPE companyType;
    private final double assets;

    /**
     * Creeaza un client de tipul 'Persoana juridica'
     *
     * @param id          id-ul clientului
     * @param name        numele clientului
     * @param address     adresa clientului
     * @param companyType tipul companiei
     * @param assets      capitalul social
     */
    public Company(int id, String name, String address, COMPANY_TYPE companyType, double assets) {
        super(id, name, address);
        this.companyType = companyType;
        this.assets = assets;
    }

    /**
     * Creeaza un string cu informatiile despre client
     *
     * @return string-ul creat
     */
    @Override
    public String convertClientInfoToString() {
        return String.format("Clientul %s(%d) companie de tipul %s cu capital de %f cu %d castiguri si %d participari.", this.getName(), this.getId(), this.companyType, this.assets, this.getNoWins(), this.getNoParticipations());
    }
}
