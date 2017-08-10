#include <iostream>

using namespace std;


class Funct {
public:
    virtual int doit(int x) = 0;
    virtual ~Funct() = 0;
};
inline Funct::~Funct() { }


class Funct1 : public Funct {
public:
    virtual int doit(int x) { /*...code from funct1...*/ }
};

class Funct2 : public Funct {
public:
    virtual int doit(int x) { /*...code from funct2...*/ }
};

class Funct3 : public Funct {
public:
    virtual int doit(int x) { /*...code from funct3...*/ }
};

typedef Funct* FunctPtr;
void myCode(FunctPtr f)
{
    // ...
    f->doit(0 /*...args-go-here...*/ );
    // ...
}



int main()
{
    cout << "Hello World!" << endl;
    FunctPtr array[10];
    array[0] = new Funct1( /*...ctor-args...*/ );
    array[1] = new Funct1( /*...ctor-args...*/ );
    array[2] = new Funct3( /*...ctor-args...*/ );
    array[3] = new Funct2( /*...ctor-args...*/ );

    return 0;
}
