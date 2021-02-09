Nume: Floarea George-Marian
Grupa: 324CB


    Administratorii pot adauga produse prin metoda lor addProduct ce e apelata in comanda 'AddProduct'. Clientii pot vizualiza
produsele prin metoda lor viewProducts. Brokerii pot sterge produsele prin metoda lor removeProduct ce e apelata la sfarsitul unei licitatii.
    In metoda askForProduct clientii comunica direct cu casa de licitatii si ii cer acesteia un produs. Casa returneaza un obiect de tipul
AuctionInfo ce contine toate informatiile necesare clientului despre licitatie, inclusiv brokerul asociat acesuita. De aici incolo,
clientul comunica cu casa de licitatii doar prin intermediul broker-ului.

    Pentru interactiunea casa de licitatii - client am folosit design pattern-ul Broker care impune ca toate comunicatiile dintre casa si client
sa se faca printr-un broker. De exemplu: la trimiterea bid-urilor clientul trimite broker-ului suma, broker-ul trimite mai departe casei toate
sumele, apoi casa intoarce bid-ul maxim, iar brokerii il trimit clientilor.

    Singurul caz cand clientrul comunica direct cu casa de licitatii este atunci cand clientul trimite o solicitare pentru un produs.
Solicitarea aceasta este procesata de casa de licitatii in metoda receiveProductRequest care trateaza 2 cazuri:
    - daca nu s-a mai cerut acest produs, atunci se creeaza o licitatie la care este inscris doar clientul ce a facut solicitarea
    - daca s-a mai cerut acest produs, atunci exista deja o licitatie creata
        - daca licitatia a inceput deja se arunca o exceptie
        - daca nu a inceput, atunci clientul este inscris la aceasta, iar daca s-au strans destui clienti se porneste licitatia

In final, aceasta metoda returneaza un obiect de tipul AuctionInfo care este adaugat in lista de licitatii la care este inscris clientul.


    Licitatia ruleaza pe un thread separat unde se fac urmatoarele operatii:
    - pentru fiecare pas al licitatiei brokerii cer sumele pe care clientii vor sa le liciteze, le trimit la casa de licitatii, apoi casa intoarce suma maxima,
se calculeaza clientul cu cel mai mare bid si se anunta toti clientii care este suma maxima licitata la acest pas
    - dupa ce s-au terminat toti pasii se verifica daca s-a licitat mai mult decat suma minima a produsului, iar daca da, brokerul muta produsul in lista
de produse vandute si isi incaseaza comisionul
    - in final, brokerii isi incheie comunicatia cu clientii



Observatii:
    - numarul de participanti necesari inceperii licitatiei a fost setat la 3
    - numarul de pasi ai licitatiei a fost setat la 3
    - suma licitata de clienti este calculata random

Design pattern-uri folosite:
    - Singleton pentru casa de licitatii
    - Builder pentru fiecare tip de produs
    - Broker pentru interactiunea client - casa de licitatii
    - Command pentru teste