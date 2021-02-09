package com.george;

/**
 * Clasa ce descrie mai concret un client de tipul persoana fizica
 */
public class Individual extends Client {
    private final String birthday;

    /**
     * Creeaza un nou client de tipul 'Persoana fizica'
     *
     * @param id       id-ul clientului
     * @param name     numele clientului
     * @param address  adresa clientului
     * @param birthday data nasterii a clientului
     */
    public Individual(int id, String name, String address, String birthday) {
        super(id, name, address);
        this.birthday = birthday;
    }

    /**
     * Creeaza un string cu informatiile despre client
     *
     * @return string-ul creat
     */
    @Override
    public String convertClientInfoToString() {
        return String.format("Clientul %s(%d) nascut la data de %s cu %d castiguri si %d participari.", this.getName(), this.getId(), this.birthday, this.getNoWins(), this.getNoParticipations());
    }
}
