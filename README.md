Hashmap.c: o strucutra de tip map, alocat dinamic, se adauga la fiecare inserare un element nou si se prelungeste dimensiunea,
        acceasi logica si la delete din tabela. Daca o cheie apare a doua oara este rescrisa valoarea ei.

Line_args.c: proceseaza argumentele si le pune intr-o structura aferenta

main.c: citesc linie cu linie, tratez fiecare instructiune # diferit.
    #define, adaug valoarea in Hashmap
    #ifdef verific valoarea, daca este definita tratez instructiunile ce urmeaza pana la endif sau else ca instructiuni normale
    #if idem dar verific diferit de 0, iar la elif reconsider conditita de if