#include "foo.h"

template<typename T>
Foo<T>::Foo(const T& value):value_(value) {
}


template<typename T>
Foo<T> operator+ (const Foo<T>& lhs, const Foo<T>& rhs) //solution1
{
    return Foo<T>(lhs.value_ + rhs.value_);
}


template<typename T>
std::ostream& operator<< (std::ostream& o, const Foo<T>& x)//solution1
{
    return o << x.value_;
}

