#include <iostream>
#include <cassert>

using namespace std;

class Fred {
public:
    static Fred create1(const std::string& s, int i);
    static Fred create2(float x, float y);
    Fred(const Fred& f);
    Fred& operator= (const Fred& f);
    ~Fred();
    void sampleInspectorMethod() const;   // No changes to this object
    void sampleMutatorMethod();           // Change this object
    // ...
private:
    class Data {
    public:
        Data() : count_(1) { }
        Data(const Data& d) : count_(1) { (void)d; }     // Do NOT copy the 'count_' member!
        Data& operator= (const Data&) { return *this; }  // Do NOT copy the 'count_' member!
        virtual ~Data() { assert(count_ == 0); }         // A virtual destructor
        virtual Data* clone() const = 0;                 // A virtual constructor
        virtual void sampleInspectorMethod() const = 0;  // A pure virtual function
        virtual void sampleMutatorMethod() = 0;
    private:
        unsigned count_;   // count_ doesn't need to be protected
        friend class Fred; // Allow Fred to access count_
    };
    class Der1 : public Data {
    public:
        Der1(const std::string& s, int i) { (void)s; (void)i; }
        virtual void sampleInspectorMethod() const override {}
        virtual void sampleMutatorMethod() override {}
        virtual Data* clone() const override;
        // ...
    };
    class Der2 : public Data {
    public:
        Der2(float x, float y) { (void)x; (void)y; }
        virtual void sampleInspectorMethod() const override {}
        virtual void sampleMutatorMethod() override {}
        virtual Data* clone() const override;
        // ...
    };
    Fred(Data* data);
    // Creates a Fred smart-reference that owns *data
    // It is private to force users to use a createXXX() method
    // Requirement: data must not be NULL
    Data* data_;   // Invariant: data_ is never NULL
};
Fred::Fred(Data* data) : data_(data)  { assert(data != nullptr); }
Fred Fred::create1(const std::string& s, int i) { return Fred(new Der1(s, i)); }
Fred Fred::create2(float x, float y)            { return Fred(new Der2(x, y)); }
Fred::Data* Fred::Der1::clone() const { return new Der1(*this); }
Fred::Data* Fred::Der2::clone() const { return new Der2(*this); }
Fred::Fred(const Fred& f):data_(f.data_) {
    ++(data_->count_);
}
Fred& Fred::operator= (const Fred& f) {
    // DO NOT CHANGE THE ORDER OF THESE STATEMENTS!
    // (This order properly handles self-assignment)
    // (This order also properly handles recursion, e.g., if a Fred::Data contains Freds)
    Data* const old = data_;
    data_ = f.data_;
    ++data_->count_;
    if ((--old->count_) == 0)
        delete old;
    return *this;
}
Fred::~Fred() {
    if ((--data_->count_) == 0)
        delete data_;
}
void Fred::sampleInspectorMethod() const {
    // This method promises ("const") not to change anything in *data_
    // Therefore we simply "pass the method through" to *data_:
    data_->sampleInspectorMethod();
}
void Fred::sampleMutatorMethod() {
    // This method might need to change things in *data_
    // Thus it first checks if this is the only pointer to *data_
    if (data_->count_ > 1) {
        Data* d = data_->clone();   // The Virtual Constructor Idiom
        --(data_->count_);
        data_ = d;
    }
    assert(data_->count_ == 1);
    // Now we "pass the method through" to *data_:
    data_->sampleMutatorMethod();
}


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
