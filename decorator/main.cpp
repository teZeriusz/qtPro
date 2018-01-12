#include <iostream>
#include <string>

using namespace std;
class Component {
public:
    virtual void operation() = 0;
};

class ConcreteComponent : public Component {
    void operation() override { cout << "pattern"; }
};

class Decorator : public Component {
    Component & component;
    void beforeOperation() { cout << "decorator "; }
    void afterOperation() { cout << "."; }
public:
    Decorator(Component & c) : component(c) { }
    void operation() override {
        beforeOperation();
        component.operation();
        afterOperation();
    }
};


int main() {
    ConcreteComponent comp1;
    Decorator dec1(comp1);
    Component &comp = dec1;
    // decorator is also a component so can be also decorated
    Decorator dec2(comp);
    dec1.operation();
    cout << endl;
    dec2.operation();
    return 0;
}
