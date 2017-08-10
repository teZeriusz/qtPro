#include <iostream>

using namespace std;

template<typename T>
class B {
public:
    class Xyz { /*...*/ };  // Type nested in class B<T>
    typedef int Pqr;        // Type nested in class B<T>
    void f() { }  // Member of class B<T>
};


template<typename T>
class D : public B<T> {
public:
    void g()
    {
        typename B<T>::Xyz x;
        typename B<T>::Pqr y;
//        f(); //error
        this->f();
        B<T>::f();


//        using B<T>::f; //GCC not working
//        f();
    }
};


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
