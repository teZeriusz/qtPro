#include <iostream>
#include <cassert>

using namespace std;

class Fred {
public:
    Fred();                               // A default constructor
    Fred(int i, int j);                   // A normal constructor
    Fred(const Fred& f);
    Fred& operator= (const Fred& f);
    ~Fred();

    void sampleInspectorMethod() const;   // No changes to this object
    void sampleMutatorMethod();           // Change this object
    // ...
private:
    class Data {
    public:
        Data();
        Data(int i, int j);
        Data(const Data& d);
        // Since only Fred can access a Fred::Data object,
        // you can make Fred::Data's data public if you want.
        // But if that makes you uncomfortable, make the data private
        // and make Fred a friend class via friend class Fred;
        // ...your data members are declared here...
        unsigned count_;
        // count_ is the number of Fred objects that point at this
        // count_ must be initialized to 1 by all constructors
        // (it starts as 1 since it is pointed to by the Fred object that created it)
    };//Data
    Data* data_;

private:
    static Data* defaultData();
    static Data* defaultData(int i, int j);
};


Fred::Data::Data()              : count_(1) /*init other data*/ { }
Fred::Data::Data(int i, int j)  : count_(1) { (void)(i); (void)(j);  }
Fred::Data::Data(const Data& d) : count_(1) { (void)(d); }
Fred::Data* Fred::defaultData() {
    static Data* p = nullptr;
    if (p == nullptr) {
        p = new Data();
        ++p->count_;    // Make sure it never goes to zero
    }
    return p;
}
Fred::Data* Fred::defaultData(int i, int j) {
    static Data* p = nullptr;
    if (p == nullptr) {
        p = new Data(i, j);
        ++p->count_;    // Make sure it never goes to zero
    }
    return p;
}

Fred::Fred()             : data_(defaultData()) { }
Fred::Fred(int i, int j) : data_(defaultData(i, j)) { }
Fred::Fred(const Fred& f)
    : data_(f.data_)
{
    ++data_->count_;
}
Fred& Fred::operator= (const Fred& f)
{
    // DO NOT CHANGE THE ORDER OF THESE STATEMENTS!
    // (This order properly handles self-assignment)
    // (This order also properly handles recursion, e.g., if a Fred::Data contains Freds)
    Data* const old = data_;
    data_ = f.data_;
    ++data_->count_;
    if (--old->count_ == 0) delete old;
    return *this;
}
Fred::~Fred()
{
    if (--data_->count_ == 0) delete data_;
}
void Fred::sampleInspectorMethod() const
{
    // This method promises ("const") not to change anything in *data_
    // Other than that, any data access would simply use "data_->..."
}
void Fred::sampleMutatorMethod()
{
    // This method might need to change things in *data_
    // Thus it first checks if this is the only pointer to *data_
    if (data_->count_ > 1) {
        Data* d = new Data(*data_);    // Invoke Fred::Data's copy ctor
        --data_->count_;
        data_ = d;
    }
    assert(data_->count_ == 1);
    // Now the method proceeds to access "data_->..." as normal
}


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
