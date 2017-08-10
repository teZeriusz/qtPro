// File "foo.cpp"
#include <iostream>
#include "foo.h"
template<typename T>
void foo()
{
  std::cout << "Here I am!\n";
}

//template void foo<int>(); //solution 1
