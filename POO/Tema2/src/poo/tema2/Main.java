package poo.tema2;

import poo.tema2.Commands.*;
import poo.tema2.Exceptions.CurrencyNotFoundException;
import poo.tema2.Exceptions.DiscountNotFoundException;
import poo.tema2.Exceptions.DuplicateCurrencyException;

import java.lang.reflect.Array;
import java.util.Arrays;
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
                case "setstorecurrency":
                    try{
                        commandManager.executeCommand(new SetStoreCurrency(store, command[1]));
                    } catch(CurrencyNotFoundException e){
                        System.err.println(e.getMessage());
                    }
                    break;
                case "updateparity":
                    try{
                        commandManager.executeCommand(new UpdateParity(store, command[1], Double.parseDouble(command[2])));
                    } catch(CurrencyNotFoundException e){
                        System.err.println(e.getMessage());
                    }
                    break;
                case "loadcsv":
                    try{
                        commandManager.executeCommand(new LoadCSV(store, command[1]));
                    } catch (RuntimeException e){
                        System.err.println(e.getMessage());
                    }
                    break;
                case "savecsv":
                    try{
                        commandManager.executeCommand(new SaveCSV(store, command[1]));
                    } catch(RuntimeException e){
                        System.err.println(e.getMessage());
                        e.printStackTrace();
                    }
                    break;

                case "listproducts":
                    commandManager.executeCommand(new ListProducts(store));
                    break;
                case "showproduct":
                    commandManager.executeCommand(new ShowProduct(store, command[1]));
                    break;
                case "listmanufacturers":
                    commandManager.executeCommand(new ListManufacturers(store));
                    break;
                case "listproductsbymanufacturer":
                    commandManager.executeCommand(new ListProductsByManufacturer(store, command[1]));
                    break;
                case "listdiscounts":
                    commandManager.executeCommand(new ListDiscounts(store));
                    break;
                case "adddiscount":
                    commandManager.executeCommand(new AddDiscount(store, command[1], command[2], Arrays.copyOfRange(command, 3, Array.getLength(command))));
                    break;
                case "applydiscount":
                    try{
                        commandManager.executeCommand(new ApplyDiscount(store, command[1], command[2]));
                    } catch(DiscountNotFoundException e){
                        System.out.println(e.getMessage());
                    }
                    break;
                case "calculatetotal":
                    commandManager.executeCommand(new CalculateTotal(store, Arrays.copyOfRange(command, 1, Array.getLength(command))));
                    break;
            }
        } while (!(command[0].equals("exit") || command[0].equals("quit")));
    }
}
