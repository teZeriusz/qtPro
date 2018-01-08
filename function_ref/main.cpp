#include <iostream>

using namespace std;


template<typename Return, typename ... Args>
class function_ref<Return(Args ...)>
{
    void * _ptr;
    Return (*_erase_fn)(void*, Args ...);
public:
    template<typename F, /*some constraints*/ >
    function_ref(F&& x) noexcept: _ptr{&f}
    {
        _erase_fn = [](void * ptr, Args ... xs) -> Return {
            return (*reinterpret_cast<F*>(*ptr))(
                        std::forward<Args>(xs)...);
        };
    }
};

int operation(function_ref<int(int, int)> f) {
    return f(1,2);
}

//TODO think about that
int operation(const std::function<int(int, int)> & f) {
    return f(1,2);
}


//TODO think about that -it is ok'sh
template<typename t>
auto operation(F && f) -> decltype(std::forward<F>(f)(1,2)) {
    return std::forward<F>(f)(1,2);
}


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
