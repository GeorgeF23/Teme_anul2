import com.george.AuctionHouse;
import com.george.COMPANY_TYPE;
import com.george.CommandManager;
import com.george.commands.RegisterClient;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class TestRegisterClient {
    AuctionHouse auctionHouse = AuctionHouse.getInstance();
    CommandManager commandManager = new CommandManager();

    @Test
    void test(){
        commandManager.executeCommand(new RegisterClient(this.auctionHouse, "George Floarea", "Mihaesti", "23042001"));
        commandManager.executeCommand(new RegisterClient(this.auctionHouse, "Marian Floarea", "Mihaesti", COMPANY_TYPE.SA, 120000));

        Assertions.assertNotNull(auctionHouse.findClientById(0));
        Assertions.assertNotNull(auctionHouse.findClientById(1));
        Assertions.assertNull(auctionHouse.findClientById(5));

    }
}
