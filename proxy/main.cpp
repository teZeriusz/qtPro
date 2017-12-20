#include <iostream>
#include <string>
#include <memory>

using namespace std;
class Subject {
public:
    virtual string method() = 0;
};

class RealSubject : public Subject {
public:
    virtual string method() override { return "proxy pattern"; }
};

class Proxy : public Subject {
    unique_ptr<RealSubject> rs;
    void createSubject() {
        if ( rs == nullptr ) {
            rs.reset(new RealSubject);
        }
    }
public:
    Proxy() {}
    virtual ~Proxy() {}
    virtual string method() override {
        // first call creates subject
        createSubject();
        return rs->method();
    }
};
void f(Subject &s) {
    cout << s.method() << endl;
}

int main() {
    Proxy proxy;
    // Proxy is subject
    f(proxy);

    return 0;
}
