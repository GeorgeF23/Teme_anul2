import com.george.Administrator;
import com.george.AuctionHouse;
import com.george.CommandManager;
import com.george.commands.AddAdministrator;
import com.george.commands.AddProduct;
import com.george.products.PaintingBuilder;
import com.george.products.Product;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;

class TestAddProduct {
    AuctionHouse auctionHouse = AuctionHouse.getInstance();
    CommandManager commandManager = new CommandManager();


    @Test
    void test1(){
        commandManager.executeCommand(new AddAdministrator(auctionHouse, "George"));
        Assertions.assertNotNull(auctionHouse.findAdministratorById(0));
        Product product = new PaintingBuilder()
                .withId(-2)
                .withName("Tablou")
                .withMinimumPrice(2500.0)
                .withYear(1924)
                .withAuthorName("Autor")
                .withColors("ULEI")
                .build();
        commandManager.executeCommand(new AddProduct(auctionHouse, 0, product));
        Assertions.assertNotNull(auctionHouse.findProductById(0));
    }

    @Test
    void test2(){
        commandManager.executeCommand(new AddAdministrator(auctionHouse, "Marian"));

        Product product = new PaintingBuilder()
                .withId(-2)
                .withName("Tablou")
                .withMinimumPrice(2500.0)
                .withYear(1924)
                .withAuthorName("Autor")
                .withColors("ULE2i")
                .build();
        commandManager.executeCommand(new AddProduct(auctionHouse, 1, product));
        Assertions.assertNull(auctionHouse.findProductById(1));
    }
}
