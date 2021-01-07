import java.util.ArrayList;

public class Store {
    private Store instance;

    private ArrayList<Currency> currencies;
    private Currency currentCurrency;

    public Store getInstance(){
        if(instance == null){
            instance = new Store();
        }
        return instance;
    }

}
