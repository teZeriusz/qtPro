#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <list>
#include <numeric>
#include <cmath>



template <typename F, typename R>
R mapf(F&& f, R r)
{
    std::transform(
                std::begin(r), std::end(r), std::begin(r),
                std::forward<F>(f));
    return r;
}


template<typename F, typename T, typename U>
std::map<T, U> mapf(F&& f, std::map<T, U> const & m)
{
    std::map<T, U> r;
    for (auto const kvp : m)
        r.insert(f(kvp));
    return r;
}

template<typename F, typename T>
std::queue<T> mapf(F&& f, std::queue<T> q)
{
    std::queue<T> r;
    while (!q.empty())
    {
        r.push(f(q.front()));
        q.pop();
    }
    return r;
}


template <typename F, typename R, typename T>
constexpr T foldl(F&& f, R&& r, T i)
{
    return std::accumulate(
                std::begin(r), std::end(r),
                std::move(i),
                std::forward<F>(f));
}

template <typename F, typename R, typename T>
constexpr T foldr(F&& f, R&& r, T i)
{
    return std::accumulate(
                std::rbegin(r), std::rend(r),
                std::move(i),
                std::forward<F>(f));
}

template <typename F, typename T>
constexpr T foldl(F&& f, std::queue<T> q, T i)
{
    while (!q.empty())
    {
        i = f(i, q.front());
        q.pop();
    }
    return i;
}


template<class T = double>
struct fround
{
    typename std::enable_if<
    std::is_floating_point<T>::value, T>::type
    operator()(const T& value) const
    {
        return std::round(value);
    }
};


template <typename F, typename T1, typename T2>
auto foldl(F&&f, T1 arg1, T2 arg2)
{
    return f(arg1, arg2);
}

template <typename F, typename T, typename... Ts>
auto foldl(F&& f, T head, Ts... rest)
{
    return f(head, foldl(std::forward<F>(f), rest...));
}


int main()
{
    {
    auto vnums =
            std::vector<int>{0, 2, -3, 5, -1, 6, 8, -4, 9};
    auto r = mapf([](int const i) {
        return std::abs(i); }, vnums);
    // r = {0, 2, 3, 5, 1, 6, 8, 4, 9}
    }
    auto lnums = std::list<int>{1, 2, 3, 4, 5};
    auto l = mapf([](int const i) {
        return i*i; }, lnums);
    // l = {1, 4, 9, 16, 25}



    auto amounts =
            std::array<double, 5> {10.42, 2.50, 100.0, 23.75, 12.99};
    auto a = mapf(fround<>(), amounts);
    // a = {10.0, 3.0, 100.0, 24.0, 13.0}


    auto words = std::map<std::string, int>{
        {"one", 1}, {"two", 2}, {"three", 3}
    };

    auto m = mapf(
                [](std::pair<std::string, int> const kvp) {
            return std::make_pair(
                mapf(toupper, kvp.first),
                kvp.second);
},
            words);
    // m = {{"ONE", 1}, {"TWO", 2}, {"THREE", 3}}

    auto priorities = std::queue<int>();
    priorities.push(10);
    priorities.push(20);
    priorities.push(30);
    priorities.push(40);
    priorities.push(50);
    auto p = mapf(
                [](int const i) { return i > 30 ? 2 : 1; },
    priorities);
    // p = {1, 1, 1, 2, 2}


    auto vnums =
            std::vector<int>{0, 2, -3, 5, -1, 6, 8, -4, 9};

    auto s1 = foldl(
                [](const int s, const int n) {return s + n; },
                vnums, 0);                // s1 = 22

    auto s2 = foldl(
                std::plus<>(), vnums, 0); // s2 = 22

    auto s3 = foldr(
                [](const int s, const int n) {return s + n; },
                vnums, 0);                // s3 = 22

    auto s4 = foldr(
                std::plus<>(), vnums, 0); // s4 = 22

using namespace std;//for literal s
    auto texts =
            std::vector<std::string>{"hello"s, " "s, "world"s, "!"s};
//TODO make string factory from this!
    auto txt1 = foldl(
                    [](std::string const & s, std::string const & n) {
                    return s + n;},
                texts, ""s);    // txt1 = "hello world!"

    auto txt2 = foldr(
                    [](std::string const & s, std::string const & n) {
                    return s + n; },
                texts, ""s);    // txt2 = "!world hello"



    char chars[] = {'c','i','v','i','c'};

    auto str1 = foldl(std::plus<>(), chars, ""s);
    // str1 = "civic"

    auto str2 = foldr(std::plus<>(), chars, ""s);
    // str2 = "civic"


    auto words2 = std::map<std::string, int>{
        {"one", 1}, {"two", 2}, {"three", 3} };

    auto count = foldl(
                [](int const s, std::pair<std::string, int> const kvp) {
        return s + kvp.second; },
    words2, 0); // count = 6

//----------PIPELINE



    auto vnums2 = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };

    auto s = foldl(
                std::plus<>(),
                mapf(
                    [](int const i) {return i*i; },
                mapf(
                    [](int const i) {return std::abs(i); },
            vnums2)),
                0); // s = 236



    std::cout << "Hello World!" << std::endl;
    return 0;
}
