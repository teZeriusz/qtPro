#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <memory_resource>

using namespace std;


struct CountingMemoryResource: public pmr::memory_resource {
    explicit CountingMemoryResource(pmr::memory_resource * parent = pmr::get_default_resource()):
        d_parent(parent), d_currentSize(0), d_maxSize(0), d_count(0) {
    }

    void * do_allocate(const size_t _Bytes, const size_t _Allign) override {
        cout << "alloc bytes:" << _Bytes << " allign:" << _Allign << endl;

        void * res = d_parent->allocate(_Bytes, _Allign);
        d_currentSize += _Bytes;
        if(d_currentSize > d_maxSize)
            d_maxSize = d_currentSize;

        ++d_count;
        return res;
    }

    void do_deallocate(void * const _Ptr, const size_t _Bytes, size_t _Align) noexcept override {
        d_parent->deallocate(_Ptr, _Bytes, _Align);
        d_currentSize -= _Bytes;
    }

    virtual bool do_is_equal(const memory_resource& _That) const noexcept override {
        return (this == &_That);
    }

private:
    pmr::memory_resource * d_parent;
    size_t d_currentSize, d_maxSize, d_count;
};



size_t unique(std::string & s1) {
    CountingMemoryResource cmr;
    pmr::set<char> a(&cmr);
    a.insert(s1.begin(), s1.end());

    return a.size();
}

int main() {
    string s1("very long string with dummy text in it that only take space and some memory");
    size_t foundCount = unique(s1);
    cout << foundCount << endl;

    return 0;
}
