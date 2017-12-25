#include <iostream>

using namespace std;

/*
Wiemy, że w systemie na 127.0.0.1:1234 słucha serwer Monitor, do którego
dokumentacja spłonęła 3 lata temu, ale zachował się jego kod w języku Python. Kod
ten przedstawiony jest poniżej. Monitor w reakcji na każde połączenie po TCP
odpowiada 50 liczbami z zakresu 0-100, oraz jedną literką.

Napisz serwer Buchalter, który:
1. raz na sekundę odpytuje Monitor o jego zestaw danych;
2. nasłuchuje na połączenia po TCP na porcie 1235, i dla każdej liczby w zapisie
dziesiętnym która zostanie wysłana na ten port (liczby mogą być oddzielone
dowolnym białym znakiem) zwróci w nowej linijce:
• dla liczby wejściowej 0: ostatnio odczytaną od Monitora literkę;
• dla liczby wejściowej X większej od zera: ilość wszystkich do tej pory
otrzymanych od Monitora liczb równych X.
• dla każdej innej liczby odeśle liczbę -1.
Swój serwer napisz w języku C dla systemu Linux. Postaraj się obsługiwać wielu
klientów równolegle, oraz zapewnić bezpieczne działanie serwera wliczając w to
niepoprawne dane wejściowe.
*/
/*
 * monitor.py
import socket, random
LISTEN_PORT = 1234
MAX_LINE_LEN = 20
def generate_msg():
    words = []
    while len(words) < 50:
        n = random.randint(0, 100)
        words.append(str(n))
    words.append(chr(random.randint(ord('a'), ord('z'))))

    msg = ''
    line = ''
    while words:
        w = words.pop(0)
        if len(line) + 2 + len(w) > MAX_LINE_LEN:
            msg += line + "\n"
            line = w
        else:
            if line:
                line += ", "
            line += w
    msg += line
return msg

def main():
    ls = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    ls.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    ls.bind(("127.0.0.1", LISTEN_PORT))
    ls.listen(128)
    while True:
        (cs, caddr) = ls.accept()
        msg = generate_msg()
        cs.send(msg)
        cs.close()

if __name__ == '__main__':
    main()
*/

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
