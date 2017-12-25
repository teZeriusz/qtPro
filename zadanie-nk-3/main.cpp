#include <iostream>

using namespace std;

/*
Zaimplementuj strukturę stosu, taką żeby efektywnie były wykonywane operacje wkładania elementu na
stos, zdejmowania oraz sprawdzanie wartości najmniejszego elementu znajdującego się na stosie.
Bardziej szczegółowo Twoim zadaniem jest napisanie klasy Stack w dowolnym wybranym przez Ciebie
języku programowania. Stos ten będzie przechowywał jedynie wartości całkowitoliczbowe. Klasa ta
powinna zawierać następujące metody:
● push – przyjmująca jeden argument, element do umieszczenia na stosie,
● pop – bezargumentowa, zdejmująca i zwracająca element ze stosu, jeżeli stos jest pusty powinien
zostać rzucony odpowiedni wyjątek,
● min – bezargumentowa, zwracająca wartość najmniejszego elementu znajdującego się na stosie
(metoda ta nie powinna zdejmować ze stosu żadnego elementu),
● empty – bezargumentowa, zwracająca true jeżeli stos jest pusty, oraz false w przeciwnym
przypadku.
*/

/*php
$stack = new Stack();
$stack->push(10);
$stack->push(7);
$stack->push(8);
$stack->push(4);
$stack->push(11);
$stack->min(); // zwraca 4
$stack->pop(); // zwraca 11
$stack->min(); // zwraca 4
$stack->pop(); // zwraca 4
$stack->min(); // zwraca 7
$stack->push(2);
$stack->min(); // zwraca 2
$stack->pop(); // zwraca 2
$stack->min(); // zwraca 7
*/



int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
