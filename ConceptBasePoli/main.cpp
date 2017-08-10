#include <iostream>
#include <memory>

using namespace std;
//concept based polimorphism
class drawable_concept {
public:
    drawable_concept() = default;
    virtual ~drawable_concept() = default;
    virtual void draw() = 0;
};

template<class T>
class drawable_model: public drawable_concept {
    T model_;
public:
    drawable_model(const T & model): model_(model) {}
    void draw() {
        model_.draw();
    }

    ~drawable_model() = default;
};

class drawable {
    std::unique_ptr<drawable_concept> object_;
public:
    template<typename T>
    drawable(const T& x): object_(new drawable_model<T>(x)) {}
    void draw() {
        object_->draw();
    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
