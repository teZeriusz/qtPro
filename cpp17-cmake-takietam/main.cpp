#include <iostream>
#include <variant>
#include <optional>
#include <any>
#include <functional>

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

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
