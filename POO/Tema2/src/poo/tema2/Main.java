package poo.tema2;

import poo.tema2.Commands.*;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
	    Store store = Store.getInstance();
	    CommandManager commandManager = new CommandManager();
	    Scanner s = new Scanner(System.in);

	    String[] command = null;

        do {
            command = s.nextLine().split("\\s+");
            switch (command[0]){
                case "listcurrencies":
                    commandManager.executeCommand(new ListCurrencies(store));
                    break;

            }
        } while (!command[0].equals("exit"));
    }
}
