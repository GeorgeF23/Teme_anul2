import com.george.AuctionHouse;
import com.george.CommandManager;
import com.george.commands.AddBroker;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;


class TestAddBroker {

    private final AuctionHouse auctionHouse = AuctionHouse.getInstance();
    private final CommandManager commandManager = new CommandManager();

    @Test
    void test1(){
        commandManager.executeCommand(new AddBroker(auctionHouse));
        Assertions.assertNotNull(auctionHouse.findBrokerById(0));
        Assertions.assertNull(auctionHouse.findBrokerById(1));
    }
}
