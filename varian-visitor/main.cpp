#include <iostream>
#include <variant>
#include <list>
#include <string>

using namespace std;

using var = std::variant<int, std::string, bool, std::list<int>>;

class Visitor {
public:
    int operator ()(std::string) {}
    int operator ()(int) {}
    int operator ()(auto) {}
};


void normal_usage() {
    Visitor visitor_obj;
    var variant_var{std::string("terefere")};
    int i = std::visit(visitor_obj, variant_var);
}


template<typename ... T>
class overload: T ... {
public:
    overload(T...t):T(t)... {}
    using T::operator()...;
};

void func(var obj) {
        std::visit(overload(
                [](int) {},
                [](std::string) {},
                [](const auto&) {} ),
            obj);
}
//tokens for a very simple calculator.

template<char>
struct C {};
struct number {double value;};
struct ident {std::string_view value;};
struct eof {};
struct remember {};
struct forget {};


using token = std::variant<
number, ident,
C<'-'>, C<'+'>, C<'/'>, C<'*'>,
C<'('>, C<')'>, C<'='>, eof, remember, forget>;

class lex {
public:
    lex(std::string s);
    token next();//consume
    token peek();//look ahead
    token drop();//consume
private://do some stuff
};


int main() {
    cout << "Hello World!" << endl;
    return 0;
}
