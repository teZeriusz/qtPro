#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;
class Prototype {
public:
    virtual unique_ptr<Prototype> clone() = 0;
};

class ConcretePrototype1 : public Prototype {
    string name;
public:
    ConcretePrototype1(const ConcretePrototype1 & t) { *this = t; }
    ConcretePrototype1 & operator=(const ConcretePrototype1 &t) {
        name = t.name;
        return  *this;
    }
    ConcretePrototype1(const string & s) : name(s) {}
    void setName(const string & s) { name = s; }
    string getName() { return name; }
    unique_ptr<Prototype> clone() override {
        unique_ptr<Prototype> copy{new ConcretePrototype1(*this)};
        return copy;
    }
};


class ConcretePrototype2 : public Prototype {
    int value;
public:
    ConcretePrototype2(const int & v) : value(v) {}
    void setValue(int v) { value = v; }
    int getValue() { return value; }
    unique_ptr<Prototype> clone() override {
        unique_ptr<Prototype> copy{new ConcretePrototype2(*this)};
        return copy;
    }
};

int main() {
    ConcretePrototype1 a("prototype design pattern");
    ConcretePrototype2 b(7);
    // make copy
    unique_ptr<Prototype> aCpy = a.clone();
    unique_ptr<Prototype> bCpy = b.clone();

    // casting Prototype to orginal type
    ConcretePrototype1 * aCpyPtr = dynamic_cast<ConcretePrototype1*>(aCpy.get());
    ConcretePrototype2 * bCpyPtr = dynamic_cast<ConcretePrototype2*>(bCpy.get());
    // change orginal object
    a.setName("XXX");
    b.setValue(111);
    // check if copy not changed
    cout << aCpyPtr->getName() << endl;
    cout << bCpyPtr->getValue() << endl;
    return 0;
}
