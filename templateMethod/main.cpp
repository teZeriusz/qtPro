#include <iostream>


using namespace std;


class ApplicationFramework {
protected:
    virtual void step1() = 0;
    virtual void step2() = 0;
public:
    void templateMethod() {
        step1();
        step2();
    }
};

class Application : public ApplicationFramework {
protected:
    void step1() override { cout << "Template method" << endl; }
    void step2() override { cout << "design pattern" << endl; }
};

void frameworkFunction(ApplicationFramework & app) {
    app.templateMethod();
}

int main() {
    Application app;
    frameworkFunction(app);

    return 0;
}
