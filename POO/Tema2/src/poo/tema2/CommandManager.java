package poo.tema2;

import poo.tema2.Commands.ICommand;

/**
 * Clasa care administreaza comenzile disponibile
 */
public class CommandManager {

    /**
     * Executa o comanda
     * @param command comanda care va fi executata
     */
    public void executeCommand(ICommand command){
        command.execute();
    }
}
