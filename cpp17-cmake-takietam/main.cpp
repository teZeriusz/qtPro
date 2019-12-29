#include <iostream>
#include <variant>
#include <optional>
#include <any>
#include <functional>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <execution>
#include <map>

using namespace std;
void variant_t1() {
    std::variant<int, double> v {12};
    std::get<int>(v); // == 12
    std::get<0>(v); // == 12
    v = 12.0;
    std::get<double>(v); // == 12.0
    std::get<1>(v); // == 12.0
}

std::optional<std::string> create(bool b) {
    if (b) {
        return "Godzilla";
    } else {
        return {};
    }
}

void optional_t1() {
    create(false).value_or("empty"); // == "empty"
    create(true).value(); // == "Godzilla"
    // optional-returning factory functions are usable as conditions of while and if
    if (auto str = create(true)) {
        // ...
    }
}

void any_t1() {
    std::any x {5};
    x.has_value(); // == true
    std::any_cast<int>(x); // == 5
    std::any_cast<int&>(x) = 10;
    std::any_cast<int>(x); // == 10
}


void string_view_t1() {
    // Regular strings.
    std::string_view cppstr {"foo"};
    // Wide strings.
    std::wstring_view wcstr_v {L"baz"};
    // Character arrays.
    char array[3] = {'b', 'a', 'r'};
    std::string_view array_v(array, std::size(array));

    std::string str {"   trim me"};
    std::string_view v {str};
    v.remove_prefix(std::min(v.find_first_not_of(" "), v.size()));
    str; //  == "   trim me"
    v; // == "trim me"
}

template <typename Callable>
class Proxy {
    Callable c;
public:
    Proxy(Callable c): c(c) {}
    template <class... Args>
    decltype(auto) operator()(Args&&... args) {
        // ...
        return std::invoke(c, std::forward<Args>(args)...);
    }
};

void invoke_t1() {
    auto add = [](int x, int y) {
        return x + y;
    };
    Proxy<decltype(add)> p {add};
    p(1, 2); // == 3
}

void apply_t1() {
    auto add = [](int x, int y) {
        return x + y;
    };
    std::apply(add, std::make_tuple(1, 2)); // == 3
}

template<typename T, typename Coll, typename ...Mxs>
void insertAsString(T t, Coll & coll, Mxs&...mutexes) {
    if constexpr(std::scoped_lock sl{mutexes...}; ! std::is_arithmetic_v<T>) {//std::lock() ?//FATAL? where are mutexes unlocked?
        coll.push_back(t);
    }
    else {
        coll.push_back(std::to_string(t));
    }
}

void test_insertAsString() {
    std::vector<std::string> strings;
    std::mutex stringsMutex;
    std::shared_mutex readonlyMutex;
    {
//        std::lock_guard lg(stringsMutex); //lock_guard<std::mutex> Class Template Argument Deduction
        insertAsString("dupa", strings, stringsMutex, readonlyMutex);

        insertAsString(42,  strings, stringsMutex);
        insertAsString(0.4, strings, stringsMutex);
    }
}


//void print(){};

template<typename T, typename ...Types>
void print(T firstArg, Types... args) {
    std::cout << firstArg << '\n';
    if constexpr(sizeof... (args) > 0)
        print(args...);
}

template<typename T>
auto spaceBefore(T arg) {
    std::cout << ' ';
    return arg;
}

template<typename ...T>
void foldPrint(T...args) {
    (cout << ... << args) << "\n";
}

template<typename First, typename ...T>
void foldPrint2(First x, T...args) {
    cout << x;
    (cout << ... << spaceBefore(args)) << "\n";
}

template<typename First, typename ...T>
void foldPrint3(const First &x, const T&...args) {
    cout << x;
    auto space = [](const auto & space_me) {
        cout << ' ' << space_me;
    };
    (... , space(args));
    cout << "\n";
}

template<auto sep = ' ',
    typename First, typename ...T>
void foldPrint4(const First &x, const T&...args) {
    cout << x;
    auto space = [](const auto & space_me) {
        cout << sep << space_me;
    };
    (... , space(args));
    cout << "\n";
}


void test_print() {
    print(14, "dup", "bladych");
    foldPrint(14, "dup", "bladych");
    foldPrint2(14, "dup", "bladych");
    foldPrint3(14, "dup", "bladych");
    foldPrint4(14, "dup", "bladych");
    foldPrint4<'-'>(14, "dup", "bladych");
    static const char sep[] = ", ";
    foldPrint4<sep>(14, "dup", "bladych");
}


template<typename ...T>
auto foldSum(T...s) {
//    return (... + s);
    return (0 + ... + s);
}

template<typename T>
void foo(T t) {

}

template<typename ...Args>
void callFoo(Args ...arg) {
//    std::initializer_list<int>{((void)foo(arg), 0) ...}; //before C++17
    (..., (void)foo(arg));//call foo with fold expression - c++17
}


auto generateStrings(size_t elemNuber) {
    vector<string> strings;
    strings.reserve(elemNuber);
    for(size_t i = 0; i < elemNuber; ++i) {
        strings.emplace_back("id" + std::to_string(i));
        strings.emplace_back("ID" + std::to_string(i));
    }

    return strings;
}

void playWithStrings() {
    auto strings = generateStrings(1000);
    sort(std::execution::seq, //par
        begin(strings), end(strings),
         [](const auto & a, const auto & b) {
             return string_view{a}.substr(2) < string_view{b}.substr(2);
         }
         );
}

void hahaha() {
    vector<int> nums{3,4,5,1,2,0,10};
//    partial_sum(nums.begin(), nums.end(),//XXX why this is not working?
//                     ostream_iterator<string>(std::cout, " "));

    inclusive_scan(std::execution::seq,
                   nums.begin(), nums.end(),
                   ostream_iterator<int>(cout, " "));
}

struct A {//NO need for base class in variant
    virtual void draw() = 0;
    virtual void move() = 0;
};

struct B{//: public A {
    void draw() {}
    void move() {}
};

struct C{//: public A {
    void draw() {}
    void move() {}
};
using derived = std::variant<B,C>;

void varian_playground() {
    vector<derived> dd;
    dd.push_back(B{});
    dd.push_back(C{});
}

void varian_in_vector(vector<derived>& d) {
    for(derived & a: d) {
        visit([](auto & el)
              {
                  el.draw();
                  if constexpr(std::is_same_v<decltype(el), C&>) {//compile time GREAT!
                      el.move();
                  }
              }, a);

        if(auto goPtr = std::get_if<C>(&a); goPtr) {//XXX not working in visit()! why?
            goPtr->move();
        }
    }
}

template<typename ...T>//XXX WTF...???
struct Ovld: T... {
    using T::operator()...;
};
template<typename...T>
Ovld(T...) -> Ovld<T...>;

void varian_in_vector2(vector<derived>& d) {
    for(auto & a: d) {
        visit(Ovld{[](auto & el){ el.draw(); },
                   [](C & c){ c.move(); }
              }, a);
    }
}
//weak_ptr
class Person {
    weak_ptr<Person> m_something;
    string m_name;
public:
    Person(const string & name):m_name(name) {
        cout << "Person ctor " << m_name << "\n";
    }
    ~Person(){
        cout << "Person dtor " << m_name << "\n";
    }

    void set_something(const shared_ptr<Person> & something) {
        m_something = something;
    }
};

void test_emplace_back() {
    vector<string> v;

    auto & s = v.emplace_back("Hello");
    s += ", ";
    s += "world";
}

//sorted vector - binary search? - compare to set <= remove to have all inserted
struct Element {
    vector<int> container;
    int id;

    void inser(int i) {
        for(auto it(container.begin()), end(container.end()); it != end; ++it) {
            if(*it >= i) {
                if(*it > i) {
                    container.insert(it, i);
                }
                return;
            }
            container.push_back(i);
        }
    }
};

void test_extract_map_node() {
    map<int, string> m{{1, "mango"}, {2, "orange"}, {3, "apple"}};

    auto handler = m.extract(2);
    handler.key() = 4;
    m.insert(move(handler)); //only move()
}
//NICE factory function
auto new_record(const char * str) {
    static int id = 0;
    map<int, string> m;
    m.emplace(++id, str);
    return m.extract(m.begin());
}

void test_new_record() {
    map<int, string> m;
    m.insert(new_record("hi"));
    m.insert(new_record("world"));
}

int main()
{
    test_insertAsString();
    test_print();

    std::string_view s1 = "abc\0\0def"; //cmon wtf
    std::string_view s2 = "abc\0\0def"sv;
    std::cout << "s1: " << s1.size() << " \"" << s1 << "\"\n";
    std::cout << "s2: " << s2.size() << " \"" << s2 << "\"\n";


    auto ptr_1 = make_shared<Person>("Dupa");
    auto ptr_2 = make_shared<Person>("Kupa");
    ptr_1->set_something(ptr_2);
    ptr_2->set_something(ptr_1);

    return 0;
}
/*
glvalue (generalized lvalue)
- had identity
rvalue
- can be moved from
lvalue
- has identity and can't be moved from
xvalue
- has identity and can be moved from
prvalue
- Does not have identity and can be moved from
*/
