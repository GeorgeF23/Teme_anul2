Nume: Floarea George-Marian
Grupa 324CB

!! In cod cand am scris client m-am referit la clientul tcp

Protocolul implementat de mine peste tcp consta in:
    - clientii tcp trimit la server "comenzi"
    - structura comenzii se afla in "client.h" si ea contine:
        - un camp "type" care poate fi:
            - SEND_ID atunci cand clientul ii trimite server-ului id-ul lui
            - SUBSCRIBE atunci cand clientul vrea sa se aboneze la un topic
            - UNSUBSCRIBE atunci cand clientul vrea sa se dezaboneze de la un topic
            - EXIT atunci cand clientul vrea sa se deconecteze
        - un union ce poate sa contina:
            - id-ul clientului
            - o structura "subscription_info" ce poate sa contina:
                - topicul la care vrea sa se aboneze / dezaboneze clientul
                - flag-ul SF

    - serverul trimite clientilor tcp structuri de tip "message_info" definite in "message.h" si care contin:
        - ip-ul clientului udp care a trimis mesajul
        - portul pe care clientul udp a trimis mesajul
        - o structura de tip "message" care contine mesajul propriu zis:
            - topicul mesajului
            - tipul mesajului
            - un union in care pot fi cele 4 tipuri de date

        - !! atunci cand serverul se inchide acesta va trimite clientilor un mesaj cu tipul CLOSE_CLIENT care ii va face pe clienti sa se inchida si ei

Rolul fisierelor:
    - list.h / list.c definesc lista simplu inlantuita generica
    - client.h / client.c contin structurile ce definesc un client si o comanda, alaturi de niste functii ce sunt folosite pentru cautarea in lista generica
    - message.h / message.c contin structurile ce definesc un mesaj, alaturi de o functie ce este folosita pentru cautarea in lista generica
    - server.h / server.c fisierele principale ale serverului (contin functia main)
    - subscriber.h / subscriber.c fisierele principale ale subscriber-ului (contin functia main)
    - tcp.h / tcp.c contin functii pentru conexiunea tcp in server
    - udp.h / udp.c contin functii pentru conexiunea udp in server
    - utils.h preluat din laborator, contine macro-ul DIE


Serverul ruleaza astfel:
    - deschide conexiunle tcp, udp
    - folosind multiplexarea IO citeste in continuu de la input-uri
        - stdin:
            - daca mesajul e exit atunci inchide serverul si clientii
            - orice altceva e considerat mesaj invalid

        - socket-ul udp:
            - primeste un mesaj
            - il redirectioneaza la clientii tcp abonati la el / il stocheaza pentru clientii deconectati, dar abonati cu SF la topicul mesajului
        
        - socket-ul tcp principal:
            - creeaza o noua conexiune cu un client
            - insereaza in lista de clienti conectati si in setul de descriptori

        - clienti:
            - primeste o comanda
            - in functie de tip executa comanda:
                - SEND_ID (clientul isi trimite id-ul catre server):
                    - daca exista deja un client conectat cu id-ul respectiv, il respinge
                    - copiaza id-ul in structura clientului care a trimis comanda
                    - daca acesta a mai fost conectat in trecut ii copiaza abonamentele si mesajele SF
                - EXIT:
                    - muta clientul din lista de clienti conectati in cea de clienti deconectati
                    - inchide socket-ul si il scoate din lista de descriptori
                - SUBSCRIBE:
                    - creeaza o noua structura de tipul "subscription_info" si ii populeaza campurile cu datele primite
                    - o insereaza in lista de abonamente ale clientului
                - UNSUBSCRIBE
                    - sterge abonamentul din lista de abonamente a clientului
    
Subscriber-ul functioneaza astfel:
    - se conecteaza la server
    - isi trimite id-ul la server
    - folosind multiplexarea IO citeste in continuu de la input-uri:
        - stdin:
            - EXIT:
                - trimite o comanda de tipul EXIT la server
                - isi inchide socket-ul
            - SUBSCRIBE:
                - extrage topicul si flag-ul sf din input
                - trimite o comanda de subscribe la server
            - UNSUBSCRIBE:
                - extrage topicul din input
                - trimite o comanda de unsubscribe la server
        - socket-ul tcp:
            - daca tipul mesajului este de close client, atunci inchide clientul
            - afiseaza mesajul, dupa regulile fiecarui tip