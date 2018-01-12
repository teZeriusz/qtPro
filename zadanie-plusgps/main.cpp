#include <iostream>

using namespace std;

/*
Rekrutacja Inżynier
oprogramowania C++ część
1
Czas na odesłanie rozwiązań: 120 minut
● Implementacja algorytmu Sleep Sort.
○ Opis (rosettacode.org): “In general, sleep sort works by starting a separate task
for each item to be sorted, where each task sleeps for an interval
corresponding to the item's sort key, then emits the item. Items are then
collected sequentially in time.”
○ Wejście: ciąg liczb naturalnych zakończonych zerem
○ Wyjście: posortowany ciąg liczb naturalnych
○ Dodatkowe: zoptymalizować algorytm tak, aby działał w takim samym czasie
dla danych “1, 2, 0” oraz “1, 9999, 0”


● Dodanie funkcjonalności do obecnego projektu
○ Opis: w przykładowym projekcie (salesmanProblem.zip) wskazać zmiany, jakie
powinny zostać wprowadzone, aby projekt można było uznać za zgodny z
wymaganiami programów klasy enterprise (np. dodanie komentarzy (w jakich
miejscach?), zmiany w sposobie podziału na pliki (jakie?) itp.). Następnie
rozbudować program o jeden, dowolnie wybrany algorytm heurystyczny
(zwracający rezultat w postaci struktury TSPresult) z wyłączeniem algorytmu
“greedy” (najbliższy sąsiad).
○ Dodatkowe: funkcjonalności należy dopisać zgodnie ze standardem C99.
Dodatkowym, bardzo dużym atutem będzie wybór trudniejszych algorytmów, w
przypadku algorytmów opierających się o sieci neuronowe lub symulowane
wyżarzanie (Simulated Annealing) oraz algorytmów genetycznych rozwiązanie
tego problemu można nadesłać w ciągu 24 h (na pozostałe 2 pozostaje wtedy
120 minut). W załączniku można znaleźć dwa dokumenty pdf przybliżające
zagadnienie.


● Stworzenie aplikacji klient serwer
○ Opis: aplikacja kliencka ma być aplikacją terminalową pozwalającą na
wprowadzanie tekstu (ASCII) i wysyłającą dane na bierząco (po wprowadzeniu
każdego znaku) do aplikacji uruchomionej po stronie serwera, która wyświetla
ten teks w terminalu. Parametrami uruchomienia aplikacji klienckiej jest IP oraz
numer portu serwera (np. program2 192.168.1.42 1234). Parametrami
wywołania aplikacji po stronie serwera ma być numer portu, na którym ma
nasłuchiwać. Aplikacja po stronie serwera ma wyświetlać informację o
nawiązaniu połączenia przez aplikację kliencką po jego ustanowieniu (jeszcze
przed wprowadzniem jakichkolwiek danych do aplikacji klienckiej).
○ Wejście: jak w opisie
○ Wyjście: jak w opisie
○ Dodatkowe: należy określić systemy operacyjne, pod kątem których napisane
są aplikacje (dowolna wersja sytemów Windows, Linux, MacOS). Dodatkowym
atutem będzie napisanie aplikacji multiplatformowej, wykorzystując np.
http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio.html
*/

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
