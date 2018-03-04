#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
#include <list>



template <typename F, typename R, typename T>
constexpr T foldl(F&& f, R&& r, T i)
{
    return std::accumulate(
                std::begin(r), std::end(r),
                std::move(i),
                std::forward<F>(f));
}

//template container?
//template data in it?
//template algo to create?
template<typename Container = std::vector<std::string>>
class StringBuilder {
    Container m_strings;
public:
    typedef typename Container::value_type InType;

public:
    //TODO figure out genereic way to insert element to container
    void add(InType && s) {
        m_strings.push_back(std::forward<InType>(s));
    }


    //TODO bind algo to factory
//    template<std::string>
//    std::string create(Algo && algo) {
    std::string create() {
        return std::accumulate(cbegin(m_strings), cend(m_strings), std::string(),
//                               std::forward<Algo>(algo));
                               [](const InType & a, const InType & b){
                                    return a + b;
                                });
    }
};


template<typename Builder, typename Iterable>
void testSpeedFun(const Iterable & iterable) {
    using namespace std;
    using namespace chrono;

    const auto start = high_resolution_clock::now();

    Builder sb;
    for(const auto & val: iterable) {
        sb.add(to_string(val));//TODO test to_string?
    }

    cout << "elapsed before create:" << duration <double, milli> (high_resolution_clock::now() - start).count() << " ms" << endl;

    auto tt = sb.create();

    auto diff = high_resolution_clock::now() - start;
    cout << "elapsed after create:" << duration <double, milli> (diff).count() << " ms" << endl;
}


std::vector<unsigned> genTestValues(unsigned size) {
    std::vector<unsigned> out(size);
    std::iota(begin(out), end(out), size);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(begin(out), end(out), g);

    return out;
}


int main()
{
    std::cout << "Hello World!" << std::endl;
    const auto & vals = genTestValues(10000);

    testSpeedFun<StringBuilder<std::vector<std::string>>>(vals);

    return 0;
}
