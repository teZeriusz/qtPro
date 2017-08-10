#include <iostream>

using namespace std;

class Empty { };
struct X { int a; };
void f()
{
    Empty a, b;
    if (&a == &b)
        cout << "impossible: report error to compiler supplier\n";

    Empty* p1 = new Empty;
    Empty* p2 = new Empty;
    if (p1 == p2)
        cout << "impossible: report error to compiler supplier\n";
}

void f(X* p)
{
    void* p1 = p;
    void* p2 = &p->a;
    if (p1 == p2)
        cout << "nice: good optimizer\n";
}

void g() {
    cout << "sizeof Empty:" << sizeof(Empty) << endl;
}

int main()
{
    cout << "Hello World!" << endl;
    f();

    X x;
    f(&x);

    g();
    return 0;
}
