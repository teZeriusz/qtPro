#include <iostream>
#include "foo.cpp"


using namespace std;



int main()
{
    cout << "Hello World!" << endl;

    Foo<int> lhs(1);
    Foo<int> rhs(2);
    Foo<int> result = lhs + rhs;
    std::cout << result;

    return 0;
}
