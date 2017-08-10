#include <iostream>

using namespace std;
#include <vector>
#include <list>



template<typename T>
struct wrap_vector {
    typedef std::vector<T> type;
};


template<typename T>
struct wrap_list {
    typedef std::list<T> type;
};


template<typename T, template<typename> class C>
struct A {
    typename C<T>::type data;  // trick to use a proxy
};



int main()
{
    cout << "Hello World!" << endl;
    A<int, wrap_vector> avi;
    A<double, wrap_list> adl;
    // ...
    return 0;
}
