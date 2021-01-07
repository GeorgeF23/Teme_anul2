package poo.tema2;

import poo.tema2.Commands.*;
import poo.tema2.Exceptions.DuplicateCurrencyException;

import java.io.IOException;
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
                case "getstorecurrency":
                    commandManager.executeCommand(new GetStoreCurrency(store));
                    break;
                case "addcurrency":
                    try{
                        commandManager.executeCommand(new AddCurrency(store, new Currency(command[1], command[2], Double.parseDouble(command[3]))));
                    } catch(DuplicateCurrencyException e){
                        System.err.println(e.getMessage());
                    }
                    break;
            }
        } while (!command[0].equals("exit"));
    }
}
