package poo.tema2.Commands;

import poo.tema2.Store;

public class GetStoreCurrency implements ICommand {
    private Store store;

    public GetStoreCurrency(Store store) {
        this.store = store;
    }

    @Override
    public void execute() {
        System.out.println(store.getCurrentCurrency().getName());
    }
}
