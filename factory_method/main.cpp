#include <iostream>
#include <string>
#include <memory>

using namespace std;
enum class ProductType
{
    PRODUCT1,
    PRODUCT2
};

class Product {
public:
    virtual string method() = 0;
};

class Product1 : public Product {
public:
    string method() override { return "Product1::method"; }
};

class Product2 : public Product {
public:
    string method() override { return "Product2::method"; }
};


class Creator {
protected:
    virtual unique_ptr<Product> factoryMethod(ProductType type) = 0;
public:
    void anOperation() {
        ProductType products[] = { ProductType::PRODUCT1, ProductType::PRODUCT2 };
        for (auto type : products) {
            unique_ptr<Product> p = factoryMethod(type);
            cout << p->method() << endl;
        }
    }
};


class ConcreteCreator : public Creator {
protected:
    unique_ptr<Product> factoryMethod(ProductType type) override {
        unique_ptr<Product> ret(nullptr);
        switch (type) {
            case ProductType::PRODUCT1:
                ret.reset(new Product1);
            break;
            case ProductType::PRODUCT2:
                ret.reset(new Product2);
            break;
            default:
            break;
        }
        return ret;
    }
};

int main() {
    ConcreteCreator cr;
    cr.anOperation();
    return 0;
}
