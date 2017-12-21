#include <iostream>
#include <string>

using namespace std;
class Target {
public:
    virtual string operation() = 0;
};

class Adaptee {
public:
    string method1() { return "Adapter"; }
    string method2() { return " pattern"; }
};

class Adapter : public Target {
    Adaptee &adaptee;
public:
    Adapter(Adaptee & a) : adaptee(a) {}
    string operation() override
    {
        return adaptee.method1() + adaptee.method2();
    }
};


void f(Target & t) {
    cout << t.operation();
}

int main() {
    Adaptee adaptee;
    // adaptation
    Adapter adapter(adaptee);
    // Adapter is also Target
    f(adapter);
    return 0;
}
