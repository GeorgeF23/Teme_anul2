Nume: Floarea George-Marian
Grupa: 324CB

Design pattern-uri folosite:
    - Singleton pe clasa Store
    - Builder pe clasa Product
    - Command pentru a implementa fiecare comanda

Descriere comenzi:
    - addcurrency: Verifica daca moneda exista deja in store, iar daca exista arunca o exceptie, altfel adauga noua moneda in store.
    - adddiscount: Adauga noul discount in lista de discount-uri.
                   De mentionat faptul ca in main functia split imparte dupa spatiu si numele discount-ului, iar in clasa corespunzatoare
                   comnezii acesteia reunesc cuvintele din nume.
    - applydiscount: Verifica daca discount-ul exista in store, daca nu arunca o exceptie.
                     Daca exista il aplic fiecarui produs si ii setez timpul aplicarii discount-ului la momentul curent.
    - calculatetotal: Iterez prin lista de id-uri primite ca parametru si daca exista un produs cu id-ul respectiv ii adaug pretul cu tot
                      cu discount la variabila "total" care la urma este afisata.
    - getstorecurrency: Afiseaza numele monedei curente de pe store.
    - listcurrencies: Itereaza prin lista de monede si afiseaza detaliile despre acestea.
    - listdiscounts: Itereaza prin lista de discount-uri si afiseaza detaliile desprea acestea. De mentionat faptul ca aici ma folosesc de functia toString.
    - listmanufacturers: Itereaza prin lista de producatori si le afiseaza numele.
    - listproducts: Itereaza prin lista de produse si le afiseaza informatiile.
    - listproductsbymanufacturer: Itereaza prin lista de produse si daca acestea au producatorul cerut le afiseaza informatiile.
    - loadcsv: Folosind biblioteca OpenCSV citesc linie cu linie fisierul dat ca parametru si adaug produsul in lista de produse.
               Pentru crearea produsului ma folosesc de Builder-ul acestuia.
    - savecsv: Iterez prin lista de produse si le adaug informatiile intr-un ArrayList. In fiecare camp al ArrayList-ului se afla un vector de String care contine
               in fiecare camp informatiile despre produs in ordinea: ID, NUME, PRODUCATOR, PRET, CANTIATE.
               Dupa ce am facut acest ArrayList il scriu in fisierul dat ca parametru folosind CSVWriter.
    - setstorecurrency: Verific daca moneda exista in store, iar daca nu exista arunt o exceptie, altfel o setez ca fiind moneda curenta.
    - showproduct: Afiseaza informatiile produsului respectiv, daca exista.
    - updateparity: Cauta daca moneda exista in store, iar daca exista ii actualizeaza paritatea.


Mentiuni:
    - In comenzile listproducts, listproductsbymanufacturer, showproduct, savecsv pretul produselor este afisat fara a lua in considerare discount-ul.
      Discount-ul se ia in calcul doar in comanda calculatetotal. Am considerat ca discount-ul este relevant doar la calculatetotal, iar la restul comenzilor
      este mai folositor pretul fara discount.