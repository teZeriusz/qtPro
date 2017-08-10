#include <iostream>
#include <vector>
#include <memory>

using namespace std;

struct Fruit{};
struct Apple : public Fruit { void apple_fct() {} /* ... */ };
struct Orange : public Fruit { /* ... */ }; // Orange doesn't have apple_fct()

vector<shared_ptr<Fruit>> v;             // vector of Apples
void f(vector<shared_ptr<Fruit>>& vf)    // innocent Fruit manipulating function
{
    vf.push_back(make_shared<Apple>()); // add orange to vector of fruit
}

void h()
{
    f(v);    // error: cannot pass a vector<Apple*> as a vector<Fruit*>
    for (size_t i=0; i<v.size(); ++i)
        static_cast<Apple*>(v[i].get())->apple_fct();
//                ->apple_fct();
}


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
