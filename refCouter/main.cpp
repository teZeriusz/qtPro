#include <iostream>

using namespace std;

class FredPtr;
class Fred {
    Fred() {}
public:
//  Fred() = delete;
  Fred(const Fred &) = delete;
  Fred & operator = (const Fred &) = delete;

  static FredPtr create();
  void debug() {
      cout << " count:" << count_;
  }

private:
  friend class FredPtr;     // A friend class
  unsigned count_ = 0;
  // count_ must be initialized to 0 by all constructors
  // count_ is the number of FredPtr objects that point at this
};
class FredPtr {
public:
    Fred* operator-> () { return p_; }
    Fred& operator* ()  { return *p_; }
    FredPtr(Fred* p)    : p_(p) { ++(p_->count_); }  // p must not be null
    ~FredPtr()           { if (--(p_->count_) == 0) delete p_; }
    FredPtr(const FredPtr& p) : p_(p.p_) { ++(p_->count_); }
    FredPtr& operator= (const FredPtr& p) {
        // DO NOT CHANGE THE ORDER OF THESE STATEMENTS!
        // (This order properly handles self-assignment)
        // (This order also properly handles recursion, e.g., if a Fred contains FredPtrs)
        Fred* const old = p_;
        p_ = p.p_;
        ++(p_->count_);
        if (--(old->count_)== 0) delete old;
        return *this;
        }
void debug() {
    cout << "FredPtr: " << this << " Fred:" << p_;
    p_->debug();
    cout << endl;
}

private:
Fred* p_;    // p_ is never NULL
};

FredPtr Fred::create() {
    Fred * f = new Fred;
    FredPtr fp(f);
    return f;
}


void t1(FredPtr p) {
    p.debug();
}

int main() {
    cout << "Hello World!" << endl;
    FredPtr fp = Fred::create();

    return 0;
}
