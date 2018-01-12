#include <iostream>
#include <tuple>

using namespace std;



class Employee {
    string m_name;
    int m_yearOfBirth;

public:
    template <size_t I, typename E>
//    requires std::is_same_v<std::decay_t<E>, Employee>
    friend decltype(auto) get(E && e) noexcept {
        if constexpr (I == 0) {
            return (std::forward<E>(e).m_name);
        }
        else if constexpr (I == 1) {
            return (std::forward<E>(e).m_yearOfBirth);
        }
    }
};


namespace std {
    template<>
    class tuple_size<Employee>: public std::integral_constant<size_t, 2>{};
}

namespace std {
    template<size_t I>
    class tuple_element<I, Employee>:
            public std::tuple_element<I, std::tuple<std::string, int>>{};
}

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
