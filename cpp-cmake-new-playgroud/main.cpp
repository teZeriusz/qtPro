#include <iostream>

using namespace std;

class Foo {
    uint64_t a[4];
public:
    Foo() {
        cout << "ctor this:" << this << endl;
    }
    ~Foo() {
        cout << "dtor this:" << this << endl;
    }

    void * operator new(size_t size) {
        Foo * foo = (Foo*)malloc(size);
        cout << "Foo::new size:" << size << endl;
        return foo;
    }
    void operator delete(void * p, size_t size) {
        cout << "Foo::delete size:" << size << " pointer:" << p << endl;
        free(p);
    }
    void * operator new[](size_t size) {
        Foo *foo = (Foo*)malloc(size);
        cout << "Foo::new[] size:" << size << endl;
        return foo;
    }
    void operator delete[](void * p, size_t size) {
        cout << "Foo::delete[] size:" << size << " pointer:" << p <<endl;
        free(p);
    }
};

int main()
{
    cout << "sizeof:" << sizeof(Foo) << endl;
    Foo * f = new Foo();
    delete f;

    Foo * fa = new Foo[3];
    cout << "8 bytes before fa:" << *(reinterpret_cast<uint64_t*>(fa) - 1) << endl;
    delete []fa;

    return 0;
}
