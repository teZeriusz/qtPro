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

class Adapter : public Target, private Adaptee {
public:
    string operation() override { return method1() + method2(); }
};

void f(Target & t) {
    cout << t.operation();
}

int main() {
    Adapter adapter;
    // Adapter is also Target
    f(adapter);
    return 0;
}
