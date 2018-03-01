#include <iostream>
#include <tuple>

using namespace std;

//https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/
//https://www.youtube.com/watch?v=WVleZqzTw2k

template <typename T, typename Parameter>
class NamedType {
public:
    explicit NamedType(T const& value) : value_(value) {}
    explicit NamedType(T&& value) : value_(std::move(value)) {}
    T& get() { return value_; }
    T const& get() const {return value_; }
private:
    T value_;
};


using Meter = NamedType<double, struct MeterParameter>;
using Width = NamedType<Meter, struct WidthParameter>;
using Height = NamedType<Meter, struct HeightParameter>;


Meter operator"" _meter(unsigned long long length)
{
    return Meter(length);
}

class Rectangle
{
    Width m_width;
    Height m_height;
public:
    Rectangle(Width w, Height h):m_width(w), m_height(h) {}


    void print() const {//soo fucking weak
        std::cout << "w:" << (m_width.get().get()) << std::endl;
    }
};


int main() {
    Rectangle r(Width(10_meter), Height(12_meter));
    r.print();

    return 0;
}
