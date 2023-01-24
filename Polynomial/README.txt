========================================================================
Autor: Bartłomiej Kachnic,                           Krakow, 24.01.2023
========================================================================

* Zawartosc:
============

Katalog Polynomial zawiera:
--------------------------------------------------------------------

I.     Implementacja wielomianów na bazie tablic (szablon, współczynniki typu T). 

            1) Poly.h - zawiera klase Poly
            2) main.cpp - program z testami klasy Poly
            3) Makefile
           
        

* Klasa Poly
=========================

-> Poly() - (konstruktor domyślny) - tworzy nowy wielomian zerowy o
  wartości domyślnej typu T.
  
-> Poly(const T* coeffs, unsigned size) - konstruktor tworzy nowy
  wielomian o współczynnikach podanych w tablicy T * coeefs. Jeśli 
  size jest równy 0 używa domyślnego konstruktora.

-> operator+ (dodawanie wielomianów) - zwraca nowy wielomian, który
  jest sumą dwóch wybranych wielomianów.

-> operator- (odejmowanie wielomianów) - zwraca nowy wielomian, który
  jest różnicą dwóch wybranych wielomianów.

-> operator* (mnożenie wielomianów) - zwraca nowy wielomian, który
  jest iloczynem dwóch wybranych wielomianów.

-> operator== (porównanie wielomianów) - zwraca true, jeśli różnica
  wielomianów daje w wyniku wielomian zerowy, w przeciwnym wypadku
  zwraca false.

-> operator!= (porównanie wielomianów) - zwraca true, jeśli różnica 
  wielomianów nie jest równa wielomianowi zerowemu, w przeciwnym wypadku
  zwraca false.

-> operator<< (wyświetlanie) - wyświetla wielomian w kolejności od
  największej potęgi do najmniejszej.

-> calcValue(T x) - funkcja bierze argument wartość x o wybranym typie Tn
    oblicza wartośc za pomocą algorytmu Hornera i  zwraca wartość 
    wielomianu o typie T.

-> clear()  - 

-> is_zero() - funkcja zwraca true, jeśli wielomian jest wielomianem zerowym
  (posiada tylko 1 współczynnik przy potędze 0), w przeciwnym wypadku
  zwraca false.

========================================================================    

------------------------------------------------------------------------

* Jak uruchomic program:
=========================

-> Aby uruchomic , nalezy wykonac komende:
   a)   make
  

========================================================================


