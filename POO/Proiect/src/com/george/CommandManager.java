package com.george;

import com.george.commands.ICommand;

/**
 * Clasa care administreaza comenzile disponibile
 */
public class CommandManager {


    /**
     * Executa o comanda
     *
     * @param command comanda care va fi executata
     */
    public void executeCommand(ICommand command) {
        try {
            command.execute();
            System.out.println("Am executat comanda " + command.toString());
        } catch (RuntimeException e) {
            e.printStackTrace();
        }
    }
}
