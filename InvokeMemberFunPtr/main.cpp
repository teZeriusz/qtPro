#include <iostream>
#include <functional>

using namespace std;
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

class Fred {
public:
    int f(char x, float y);
    int g(char x, float y);
    int h(char x, float y);
    int i(char x, float y);
    // ...
};
typedef  int (Fred::*FredMemFn)(char x, float y);  // Please do this!

void userCode(Fred& fred, FredMemFn p)  // Use a typedef for pointer-to-member types
{
    int ans = std::invoke(p, fred, 'x', 3.14);
    int ans2 = CALL_MEMBER_FN(fred,p)('x', 3.14);
    // Would normally be: int ans = (fred.*p)('x', 3.14);
    // ...
}



FredMemFn a[] = { &Fred::f, &Fred::g, &Fred::h, &Fred::i };

void userCode(Fred& fred, int memFnNum)
{
    // Assume memFnNum is between 0 and 3 inclusive:
    std::invoke(a[memFnNum], fred, 'x', 3.14);
    CALL_MEMBER_FN(fred, a[memFnNum]) ('x', 3.14);
}


int main()
{
    cout << "Hello World!" << endl;
//    FredMemFn p = &Fred::f;
    return 0;
}
