#include <iostream>
#include <string>

using namespace std;
class Singleton {
    Singleton() {}
    Singleton(const singleton &);
    Singleton& operator=(const Singleton&);
    ~Singleton() {}
public:
    string method() { return "singleton pattern"; }

    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
};

int main() {
    Singleton& s = Singleton::getInstance();
    cout << s.method() << endl;

    return 0;
}
