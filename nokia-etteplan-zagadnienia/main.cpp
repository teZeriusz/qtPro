#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <variant>

using namespace std;

/*
Przykłady różnic pomiędzy C++ 11 a 14, 14 a 17, czy miałeś z nimi jakieś doświadczenia.
Describe override, inheritance, and polymorphism in C++. [D]
vinterface base class (how force abstraction) [D]
Multi-inheritance, deadly diamond of death problem [D]
Are you familiar with approach that destructors should be always virtual? [D]
*/
//Give some example of STL container. How to search or iterate through them? [D]
void iter() {
    std::vector<int> v{4,5,7,9,0,1,23,4};
    for(const auto & el: v) {
        cout << el << ' ';
    }
    cout << '\n';
    std::vector<int> lookFor{9,0,1};

    auto it = std::search(v.cbegin(), v.cend(), lookFor.cbegin(), lookFor.cend());
    if(it != v.end()) {
        cout << "found:" << *it;
        cout << " on pos:" << std::distance(v.cbegin(), it) << '\n';
    }
    else {
        cout << "not found\n";
    }
}

/*
Explain differences between class and structure. [D]
*/

//Benefits and disadvantages of using static data members.
//No this - 'bind' more to class then object

/*
What are auto_ptr/unique_ptr/shared_ptr, describe differences?
*/

//Why lambdas are some fancy in modern C++, write simplest example? [D]
void lambda() {
    std::vector<int> v{4,5,7,9,0,1,23,4};
    auto it = std::find_if(v.cbegin(), v.cend(), [](const int & i){return i == 0;});
    if(it != v.cend()) {
        cout << "found:" << *it << '\n';
    }
}
/*
Do you use design patterns? Which ones? Do you see any risks with using design patterns in your code?

Design Patterns therefore provide the following benefits.

- They give the developer a selection of tried and tested solutions to work with
- They are language neutral and so can be applied to any language that supports object-orientation
- They aid communication by the very fact that they are well documented and can be researched if that is not the case.
- They have a proven track record as they are already widely used and thus reduce the technical risk to the project
- They are highly flexible and can be used in practically any type of application or domain
*/

/*
How to you make your code testable? How do you make your code reusable?
- good separation/easy to write test - easy to init code to test
- limited number of singletons
- run time of tests
- easy to run
*/

//What risks are present when a function that is supposed to be thread-safe can throw an exception? How can you guard against it? [D]
std::exception_ptr eptr = nullptr;
void run_in_thread() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        try {
        while(true) {
            //do something
            throw std::exception();
        }
        }
        catch(...) {
            eptr = std::current_exception();
            return;
        }
    }
}
void thread_test() {
    std::thread t1(run_in_thread);
    t1.join();
    try {
        if(eptr) {
            std::rethrow_exception(eptr);
        }
    }
    catch(const std::exception& e) {
        std::cout << "Caught exception \"" << e.what() << "\"\n";
    }
}
//c++17 - c++20s
//http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2131r0.html
//różnice 11/14/17

//c++11 - c++14
//http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2018/p1319r0.html
/*
 * Polymorphic lambdas
 * Generalized lambda capture
 * Variable templates
 * Binary integer literals
 * Digit separators
 * [[deprecated]] attribute
 * Creation function make_unique
 * Algorithm exchange
 * Heterogeneous lookup for associative containers
 * A shared mutex
 * Compile-time integer sequences
 * Quoted strings
 * User-defined literals - for strings and chrono for complex
 * */

//c++14 - c++17
//http://open-std.org/JTC1/SC22/WG21/docs/papers/2017/p0636r2.html
/*
 * Remove trigraphs
 * Remove register
 * Remove ++ for bool
 * Remove throw(A, B, C)
 * Deprecate redeclaration of static constexpr class members
 * Remove auto_ptr, random_shuffle, old parts of <functional>
 * Remove deprecated iostream aliases
 * Remove allocator support from function
 * Deprecate C library headers
 * Deprecate old library parts
 * Deprecate <codecvt>
 * Deprecate memory_order_consume temporarily
 * Deprecate shared_ptr::unique
 * Deprecate result_of
 *
 * Exception specification as part of the type system
 * Guaranteed copy elision
 * Dynamic allocation of over-aligned types
 * Stricter order of expression evaluation
 */

//wątki deadlock/spinlock
//https://pl.wikipedia.org/wiki/Zakleszczenie

//async/future

//DP - pub/sub(observer), strategy, command, visitor(double dispath)
//visitor(double dispath)
//https://stackoverflow.com/questions/3262811/what-is-single-and-double-dispatch#3262906
//https://cpppatterns.com/patterns/visitor.html




//--------------playground - not related ----------------------
struct Triangle {
    void Render() { cout << "Drawing a triangle!\n"; }
};

struct Polygon {
    void Render() { cout << "Drawing a polygon!\n"; }
};

struct Sphere {
    void Render() { cout << "Drawing a sphere!\n"; }
};

void test_variant_visitor() {
    using Renderable = std::variant<Triangle, Polygon, Sphere>;
    std::vector<Renderable> vecRender {
        Polygon(), Triangle(), Sphere(), Triangle()
    };

    auto CallRender = [](auto& obj) { obj.Render(); };

    for(auto& obj : vecRender )
        std::visit(CallRender, obj);
}

int main()
{
    cout << "Hello World!" << endl;
    iter();
    lambda();
    thread_test();
    test_variant_visitor();
    return 0;
}
