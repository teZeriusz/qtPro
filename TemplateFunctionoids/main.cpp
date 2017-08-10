#include <iostream>
#include <vector>

using namespace std;
class Funct1 {
public:
    Funct1(float y) : y_(y) { }
    int operator()(int x) { /*...code from funct1...*/ }
private:
    float y_;
};
class Funct2 {
public:
    Funct2(const std::string& y, int z) : y_(y), z_(z) { }
    int operator()(int x) { /*...code from funct2...*/ }
private:
    std::string y_;
    int z_;
};
class Funct3 {
public:
    Funct3(const std::vector<double>& y) : y_(y) { }
    int operator()(int x) { /*...code from funct3...*/ }
private:
    std::vector<double> y_;
};



template <typename FunctObj>
void myCode(FunctObj f)
{
    // ...
    f(0 /*...args-go-here...*/ );
    // ...
}

void blah()
{
    // ...
    Funct2 x("functionoids are powerful", 42);
    myCode(x);
    // ...
}


void myNormalFunction(int x) {}
void blah2()
{
    // ...
    myCode(myNormalFunction);
    // ...
}


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
