//code

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <utility>
void y(int&) { std::cout << '1'; }
void y(int&&) { std::cout << '2'; }
template <typename T> void f(T && x) { y(x); }
template <typename T> void g(T && x) { y(std::move(x)); }
template <typename T> void h(T && x) { y(std::forward<T>(x)); }
int main() {
int i = 42;
y(i), y(42);//12
f(i), f(42);//11
g(i), g(42);//22
h(i), h(42);//12

std::stringstream ss;
ss << "ala ma kota a ola ma psa";
   std::vector<std::string> tere{std::istream_iterator<std::string>{ss},
                                 std::istream_iterator<std::string>{}};


std::cout << '\n';
   for(auto s: tere) {
    std::cout << "s:" << s << std::endl;
}
std::cout << '\n';
}

//out: 12112212
