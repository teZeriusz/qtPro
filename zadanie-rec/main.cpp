#include <iostream>
#include <algorithm>
#include <chrono>
#include <functional>
#include <vector>


using namespace std;


void testSpeedFun(const vector<unsigned> & vals, std::function<unsigned(unsigned)> fun) {
    const auto start = chrono::high_resolution_clock::now();

    for(const unsigned & val: vals) {
        fun(val);
    }

    const auto end = chrono::high_resolution_clock::now();

    auto diff = end - start;
    cout << "elapsed:" << chrono::duration <double, milli> (diff).count() << " ms" << endl;
}


struct byte {
    bool bit0 : 1;
    bool bit1 : 1;
    bool bit2 : 1;
    bool bit3 : 1;
    bool bit4 : 1;
    bool bit5 : 1;
    bool bit6 : 1;
    bool bit7 : 1;
};

union UU {
    unsigned _t;
    byte tab[sizeof(unsigned)];
} UU;

unsigned t1(unsigned t) {
    UU._t = t;

    return accumulate(begin(UU.tab), end(UU.tab), 0u, [](unsigned & uh, const byte & by) {
        uh += by.bit0 + by.bit1 + by.bit2 + by.bit3 + by.bit4 + by.bit5 + by.bit6 + by.bit7;
        return uh;
    });
}


unsigned t2(unsigned n) {
    unsigned c;
    for(c = 0; n; c++) {
        n &= n - 1;
    }
    return c;
}


vector<unsigned> genTestValues(unsigned size) {
    vector<unsigned> out(size);
    iota(begin(out), end(out), size);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(begin(out), end(out), g);

    return out;
}


int my__builtin_popcnt(unsigned n) {
    int count;
    {
        asm("popcnt %1,%0" : "=r"(count) : "rm"(n) : "cc");
    }

    return count;
}

//direct put in bind not working - linker cannot find it
int my__builtin_popcount(unsigned n) {
    return __builtin_popcount(n);
}


int main() {
    const vector<unsigned> & out = genTestValues(1000000);

    function<void()> runTest1 = bind(testSpeedFun, out, t1);
    function<void()> runTest2 = bind(testSpeedFun, out, t2);
    function<void()> runTest3 = bind(testSpeedFun, out, my__builtin_popcnt);
    function<void()> runTest4 = bind(testSpeedFun, out, my__builtin_popcount);


    cout << "t1: ";
    runTest1();

    cout << "t2: ";
    runTest2();

    if (__builtin_cpu_supports ("popcnt")) {
        cout << "t3: ";
        runTest3();

        cout << "t4: ";
        runTest4();
    }

    return 0;
}
