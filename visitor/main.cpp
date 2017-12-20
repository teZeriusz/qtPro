#include <iostream>
#include <vector>


using namespace std;

class ConcreteElementA;
class ConcreteElementB;

class Visitor {
public:
    virtual void visitConcreteElementA(ConcreteElementA& visitable) = 0;
    virtual void visitConcreteElementB(ConcreteElementB& visitable) = 0;
};


class ConcreteVisitor : public Visitor {
public:
    void visitConcreteElementA(ConcreteElementA& visitable) override
    {
        cout << "ConcreteVisitor perform opetation on ConcreteElementA" << endl;
    }
    void visitConcreteElementB(ConcreteElementB& visitable) override
    {
        cout << "ConcreteVisitor perform operation on ConcreteElementB" << endl;
    }

};


class Visitable {
public:
    virtual void accept(Visitor& visitor) = 0;
};


class ConcreteElementA : public Visitable {
public:
    void accept(Visitor &visitor) override { visitor.visitConcreteElementA(*this); }
};


class ConcreteElementB : public Visitable {
public:
    void accept(Visitor &visitor) override { visitor.visitConcreteElementB(*this); }
};

// Composite in practice
class ObjectStructure : public Visitable {
    vector<Visitable*> elements;
public:
    ObjectStructure() {}
    void addElement(Visitable *element) { elements.push_back(element); }
    void accept(Visitor &visitor) override
    {
        for (auto &e : elements)
        {
            e->accept(visitor);
        }
    }
};


int main() {
    ConcreteVisitor visitor;
    ConcreteElementA elementA;
    ConcreteElementB elementB;
    ObjectStructure objectStructure;
    objectStructure.addElement(&elementA);
    objectStructure.addElement(&elementB);
    objectStructure.accept(visitor);
    return 0;
}
