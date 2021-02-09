import com.george.AuctionHouse;
import com.george.CommandManager;
import com.george.commands.*;
import com.george.products.PaintingBuilder;
import com.george.products.Product;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class TestAskForProduct {
    AuctionHouse auctionHouse = AuctionHouse.getInstance();
    CommandManager commandManager = new CommandManager();

    @Test
    void test1() {
        commandManager.executeCommand(new AddAdministrator(auctionHouse, "Marian"));
        commandManager.executeCommand(new AddBroker(auctionHouse));
        commandManager.executeCommand(new AddBroker(auctionHouse));
        Assertions.assertNotNull(auctionHouse.findAdministratorById(0));

        commandManager.executeCommand(new RegisterClient(auctionHouse, "George", "Valcea", "230401"));

        Product product = new PaintingBuilder()
                .withId(-2)
                .withName("Tablou")
                .withMinimumPrice(2500.0)
                .withYear(1924)
                .withAuthorName("Autor")
                .withColors("ULEI")
                .build();
        commandManager.executeCommand(new AddProduct(auctionHouse, 0, product));

        Assertions.assertNotNull(auctionHouse.findClientById(0));
        Assertions.assertNotNull(auctionHouse.findProductById(0));

        commandManager.executeCommand(new ClientAskForProduct(auctionHouse, 0, 0, 2500));

        Assertions.assertEquals(1, auctionHouse.findClientById(0).getAuctionsJoined().size());
    }

    @Test
    void test2(){
        System.out.println();
        commandManager.executeCommand(new AddAdministrator(auctionHouse, "Marian"));
        commandManager.executeCommand(new AddBroker(auctionHouse));
        commandManager.executeCommand(new AddBroker(auctionHouse));
        Assertions.assertNotNull(auctionHouse.findAdministratorById(0));

        commandManager.executeCommand(new RegisterClient(auctionHouse, "George", "Valcea", "230401"));
        commandManager.executeCommand(new RegisterClient(auctionHouse, "Marian", "Valcea", "230401"));
        commandManager.executeCommand(new RegisterClient(auctionHouse, "Floarea", "Valcea", "230401"));
        commandManager.executeCommand(new RegisterClient(auctionHouse, "Gabriel", "Valcea", "230401"));


        Product product = new PaintingBuilder()
                .withId(-2)
                .withName("Tablou")
                .withMinimumPrice(2500.0)
                .withYear(1924)
                .withAuthorName("Autor")
                .withColors("ULEI")
                .build();
        commandManager.executeCommand(new AddProduct(auctionHouse, 0, product));

        commandManager.executeCommand(new ClientAskForProduct(auctionHouse, 0, 1, 2500));
        commandManager.executeCommand(new ClientAskForProduct(auctionHouse, 1, 1, 3400));
        commandManager.executeCommand(new ClientAskForProduct(auctionHouse, 2, 1, 7000));
        commandManager.executeCommand(new ClientAskForProduct(auctionHouse, 3, 1, 120));

        while(auctionHouse.getAuctions().get(1).getThreadReference().isAlive()){

        }
    }
}
