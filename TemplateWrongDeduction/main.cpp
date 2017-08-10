#include <iostream>

using namespace std;


class Xyz { /*...*/ };  // Global ("namespace scope") type
void f() { }            // Global ("namespace scope") function


template<typename T>
class B {
public:
    class Xyz { /*...*/ };  // Type nested in class B<T>
    void f() { }            // Member of class B<T>
};


template<typename T>
class D : public B<T> {
public:
    void g()
    {
        Xyz x;  // Suprise: you get the global Xyz!!
        f();    // Suprise: you get the global f!!
    }
};


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
