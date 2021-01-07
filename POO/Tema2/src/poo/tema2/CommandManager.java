package poo.tema2;

import poo.tema2.Commands.ICommand;

/**
 * Class that manages the commands.
 */
public class CommandManager {

    /**
     * Executes a command
     * @param command the command to execute
     */
    public void executeCommand(ICommand command){
        command.execute();
    }
}
