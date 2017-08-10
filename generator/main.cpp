#include <iostream>
#include <functional>
#include <memory>

using namespace std;

std::function<int(void)> makeCounter(int initial) {
   std::shared_ptr<int> count(new int(initial));
   return std::function<int(void)>([=]{ return (*count)++; });
}

int main()
{
    cout << "Hello World!" << endl;
    auto counter = makeCounter(5);
    std::cout << counter() << std::endl;
    std::cout << counter() << std::endl;
    std::cout << counter() << std::endl;

    return 0;
}
