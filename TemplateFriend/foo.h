#include <iostream>
//MUST BE BEFORE CLASS FOO
template<typename T=int> class Foo;  // pre-declare the template class itself
template<typename T> Foo<T> operator+ (const Foo<T>& lhs, const Foo<T>& rhs);//solution1
template<typename T> std::ostream& operator<< (std::ostream& o, const Foo<T>& x);//solution1

template<typename T>
class Foo {
public:
  Foo(const T& value = T());
  friend Foo<T> operator+ <> (const Foo<T>& lhs, const Foo<T>& rhs);
  //solution2
//  friend Foo<T> operator+ (const Foo<T>& lhs, const Foo<T>& rhs)
//  {
//      return Foo<T>(lhs.value_ + rhs.value_);
//  }
  friend std::ostream& operator<< <> (std::ostream& o, const Foo<T>& x);
  //solution2
//  friend std::ostream& operator<< (std::ostream& o, const Foo<T>& x)
//  {
//      return o << x.value_;
//  }
private:
  T value_;
};
