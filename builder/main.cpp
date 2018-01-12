#include <iostream>
#include <string>

using namespace std;
class Product {
    string parts;
public:
    Product() {}
    ~Product(){}
    void addPart(string part) { parts += part + "\n"; }
    string getParts() { return parts; }
};


class Buider {
public:
    virtual void buildPart1() = 0;
    virtual void buildPart2() = 0;
};

class ConcreteBuilder1 : public Buider {
    Product product;
public:
    void buildPart1() override {
        product.addPart("Builder");
    }
    void buildPart2() override {
        product.addPart("pattern");
    }
    Product & getProduct() { return product; }
};

class ConcreteBuilder2 : public Buider {
    Product product;
public:
    void buildPart1() override {
        product.addPart("Pattern");
    }
    void buildPart2() override {
        product.addPart("builder");
    }
    Product & getProduct() { return product; }
};


class Director {
    Buider& builder;
public:
    Director(Buider & b) : builder(b) {}
    void construct() {
        builder.buildPart1();
        builder.buildPart2();
    }
};


int main() {
    ConcreteBuilder1 builder1;
    ConcreteBuilder2 builder2;
    Director director1(builder1);
    Director director2(builder2);
    director1.construct();
    director2.construct();
    Product & product1 = builder1.getProduct();
    cout << product1.getParts();
    Product & product2 = builder2.getProduct();
    cout << product2.getParts();
    return 0;
}
