#include <iostream>
#include <string>
#include <map>
#include <set>
#include <memory>

using namespace std;
class Flyweight {
    string state;
public:
    Flyweight(const string& s) { state = s; }
    ~Flyweight() {}
    string doSomething(const string& s) { return s + " " + state; }
};

class FlyweightFactory {
    map<string, unique_ptr<Flyweight>> flyweights;

    bool flyweightExist(const string& key) {
        return flyweights.find(key) != flyweights.end();
    }
public:
    FlyweightFactory() {}
    ~FlyweightFactory() {}
    Flyweight & getFlyweight(const string& key) {
        if (!flyweightExist(key))
            flyweights[key] = unique_ptr<Flyweight>(new Flyweight(key));
        return *flyweights[key];
    }
    int getFlyweightsNumber() { return flyweights.size(); }
};


int main() {
    FlyweightFactory factory;
    set<string> colors{ "red", "green", "blue" };
    set<string> shades{ "pale", "dark", "light" };
    for (auto & s : shades) {
        for (auto & c : colors) {
            Flyweight &flyweight = factory.getFlyweight(c);
            cout << flyweight.doSomething(s) << endl;
        }
    }

    cout << "getFlyweightsNumber : ";
    cout << factory.getFlyweightsNumber() << endl;
    return 0;
}
