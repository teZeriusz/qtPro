#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
enum class ProductAType
{
    TYPE1,
    TYPE2
};

class AbstractProductA {
public:
    virtual string method1() = 0;
};

class ProductAF1T1 : public AbstractProductA {
public:
    string method1() override { return "ProductAF1T1::method1"; }
};

class ProductAF1T2 : public AbstractProductA {
public:
    string method1() override { return "ProductAF1T2::method1"; }
};

class ProductAF2T1 : public AbstractProductA {
public:
    string method1() override { return "ProductAF2T1::method1"; }
};

class ProductAF2T2 : public AbstractProductA {
public:
    string method1() override { return "ProductAF2T2::method1"; }
};


class AbstractProductB {
public:
    virtual string method2() = 0;
};

class ProductBF1 : public AbstractProductB {
public:
    string method2() override { return "ProductB1::method2"; }
};

class ProductBF2 : public AbstractProductB {
public:
    string method2() override { return "ProductB2::method2"; }
};


class AbstractFactory {
public:
    virtual unique_ptr<AbstractProductA> createProductA(ProductAType type) = 0;
    virtual unique_ptr<AbstractProductB> createProductB() = 0;
};


class ConcreteFactory1 : public AbstractFactory {
public:
    unique_ptr<AbstractProductA> createProductA(ProductAType type) override {
        unique_ptr<AbstractProductA> ret(nullptr);
        switch (type) {
            case ProductAType::TYPE1:
                ret.reset(new ProductAF1T1);
            break;
            case ProductAType::TYPE2:
                ret.reset(new ProductAF1T2);
            default:
            break;
        }
        return ret;
    }
    unique_ptr<AbstractProductB> createProductB() override {
        unique_ptr<AbstractProductB> pB(new ProductBF1);
        return pB;
    }
};

class ConcreteFactory2 : public AbstractFactory {
public:
    unique_ptr<AbstractProductA> createProductA(ProductAType type) override {
        unique_ptr<AbstractProductA> ret(nullptr);
        switch (type) {
            case ProductAType::TYPE1:
                ret.reset(new ProductAF2T1);
            break;
            case ProductAType::TYPE2:
                ret.reset(new ProductAF2T2);
            default:
            break;
        }
        return ret;
    }
    unique_ptr<AbstractProductB> createProductB() override {
        unique_ptr<AbstractProductB> pB(new ProductBF2);
        return pB;
    }
};
// This class shows that client code can switch easy between different factories
class CtxClass {
    AbstractFactory *factory;
public:
    CtxClass(AbstractFactory& f) : factory(&f) {}
    void setFactory(AbstractFactory& f) { factory = &f; }
    void doSomething() {
        ProductAType products[] = { ProductAType::TYPE1, ProductAType::TYPE2 };
        for (auto type : products) {
            unique_ptr<AbstractProductA> productA = factory->createProductA(type);
            cout << productA->method1() << endl;
        }
        unique_ptr<AbstractProductB> productB = factory->createProductB();
        cout << productB->method2() << endl;
    }
};

int main() {
    ConcreteFactory1 factory1;
    ConcreteFactory2 factory2;
    CtxClass ctx(factory1);
    ctx.doSomething();
    ctx.setFactory(factory2);
    ctx.doSomething();
    return 0;
}
