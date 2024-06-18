Problemy płaszczaków

Twórcy projektu:
Michał Wiśniewski
Dominik Kuźmiński
Michał Suszek
Nikodem Kaliński


Spis treści
Wprowadzenie
Problemy i ich rozwiązania
Problem nr 1
Problem nr 2
Problem nr 3
Podsumowanie
Wprowadzenie
Projekt "Problemy płaszczaków" został stworzony przez zespół składający się z Michała Wiśniewskiego, Dominika Kuźmińskiego, Michała Suszka i Nikodema Kalińskiego. Celem projektu było rozwiązanie trzech złożonych problemów algorytmicznych, z którymi twórcy się zetknęli podczas prac nad różnymi aspektami informatyki.

Problemy i ich rozwiązania

Problem nr 1
Osoba odpowiedzialna: Dominik Kuźmiński

Opis problemu: Podczas pracy nad projektem, pan Dominik natknął się na problem związany ze znalezieniem otoczki wypukłej.

Rozwiązanie: Do rozwiązania tego problemu, pan Dominik użył algorytmu Jarvisa, który pozwala na efektywne znalezienie otoczki wypukłej zbioru punktów w czasie O(n log n).

Algorytm Jarvisa:
Sortowanie: Najpierw punkty są sortowane według kąta, jaki tworzą z punktem startowym (najczęściej o najmniejszej współrzędnej y).
Budowanie otoczki: Następnie iteracyjnie dodaje się punkty do otoczki, usuwając te, które powodują wklęsłość.
Problem nr 2
Osoba odpowiedzialna: Michał Wiśniewski

Opis problemu: Pan Michał zajął się problemem związanym z zamianą słów w tekście. Początkowo natknął się na problem, który wymagał efektywnego wyszukiwania wzorców w tekście.

Rozwiązanie: Do tego celu użył algorytmu Boyera-Moore'a, który jest jednym z najefektywniejszych algorytmów wyszukiwania wzorców w tekście.

Algorytm Boyera-Moore'a:
Heurystyki: Algorytm używa dwóch heurystyk - złej przesunięcia znaku i dobrej przesunięcia sufiksu - aby szybko przeskakiwać fragmenty tekstu, które nie mogą zawierać wzorca.
Następnym problemem, którym zajął się pan Michał, było wpisywanie słów do maszyny informatycznej.

Rozwiązanie: Pan Michał skorzystał z algorytmu Huffmana, który służy do kompresji danych, tworząc drzewo Huffmana.

Algorytm Huffmana:
Kompresja: Algorytm generuje prefiksowe kody binarne, które są przypisywane do każdego znaku w taki sposób, aby najczęściej występujące znaki miały najkrótsze kody.
Problem nr 3
Osoba odpowiedzialna: Michał Suszek

Opis problemu: Pan Michał Suszek napotkał problem związany z optymalnym patrolowaniem płotu.

Rozwiązanie: Pan Michał użył do tego rozwiązania naiwnego, które polega na sekwencyjnym przechodzeniu wzdłuż płotu i wykonywaniu patrolu.

Rozwiązanie patrolowania płotu:
Opis: W najprostszym podejściu, patrolowanie odbywa się poprzez liniowe przechodzenie od jednego końca płotu do drugiego, co jest łatwe do zaimplementowania, ale niekoniecznie optymalne pod względem czasu czy zasobów.
Podsumowanie
Projekt "Problemy płaszczaków" był wyzwaniem, które wymagało zastosowania różnych algorytmów do rozwiązania złożonych problemów. Każdy z członków zespołu wniósł swoją unikalną wiedzę i umiejętności, co pozwoliło na efektywne rozwiązanie napotkanych problemów.

testy::


problem 1 Dane wejściowe:

Podaj liczbe punktow orientacyjnych oraz ilosc sciezek:
11 16

Podaj wspolrzedne kazdego z wierzcholkow:
7 12
15 0
11 9
1 10
12 5
4 5
9 7
2 2
14 11
5 8
17 6

Podaj sciezki (punkt 1, puntk 2, dlugosc drogi):
0 1 3.2
0 3 2
0 4 5.4
1 2 3
1 7 4
2 5 1
3 4 3
3 5 1.25
4 8 4
5 6 3
5 7 2
6 8 8
7 9 5
7 10 6
8 10 2.5
9 10 7

Wybierz punkt orintacyjny w ktorym jest polozona fabryka (od 0 do 10): 7

Podaj liczbe tragarzy:
10

Podaj ile tragarzy sie wzajemnie lubi:
9

Podaj po kolei tragarzy ktorzy sie lubia:
0 5
0 7
1 8
1 9
2 6
2 7
3 7
3 8
4 7

Dane wyjściowe:
Plaszczaki postawily plot w czasie: 430 minut
Ilosc zuzytych Kijkow: 38


problem2![obraz](https://github.com/mwwisn/Plaszczak_never_lies/assets/158228165/2d9f65c6-e8ac-4b1f-a102-abb4be2b069a)

Dominik Kuźmiński rozwiązał problem otoczki wypukłej za pomocą algorytmu Jarvisa.
Michał Wiśniewski zastosował algorytm Boyera-Moore'a do wyszukiwania wzorców oraz algorytm Huffmana do kompresji danych.
Michał Suszek opracował metodę patrolowania płotu.
Praca zespołowa i interdyscyplinarne podejście umożliwiły skuteczne rozwiązanie wszystkich problemów, z jakimi zespół się zetknął.
