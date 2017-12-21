#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;
template<typename T>
class Iterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual T& current() = 0;
};

template<typename T>
class VectorIterator : public Iterator<T> {
    vector<T> vect;
    size_t position;
public:
    VectorIterator(vector<T> & v) : vect(v), position(0) {}
    void first() override {
        position = 0;
    }
    void next() override {
        ++position;
    }
    bool isDone() const override {
        return !(position < vect.size());
    }
    T& current() override {
        if (!isDone()) {
            return vect.at(position);
        }
        throw out_of_range("out of range");
    }
};

int main() {
    vector<int> v{ 1, 2, 3 };
    VectorIterator<int> vIter(v);
    // use interface so you can switch easly in case different implementation
    Iterator<int> &iter = vIter;
    for (iter.first(); !iter.isDone(); iter.next()) {
        cout << iter.current() << endl;
    }
    return 0;
}
