#include<iostream>
#include<thread>
#include<random>
#include<chrono>
#include<atomic>
#include<map>

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

//policy based design class
template<typename OutputPolicy, typename LanguagePolicy>
class HelloWord:
        private OutputPolicy,
        private LanguagePolicy {
    using OutputPolicy::print;
    using LanguagePolicy::message;

public:
    void run() const {
        print(message());
    }
};

//curiously recurring template pattern
typedef int awesome;
template<class T>
struct Base {
    awesome foonathan() {
        static_cast<T*>(this)->i++;
        return static_cast<T*>(this)->something();
    }
};

struct Derived: public Base<Derived> {
    int i;
    awesome something();
    //...
};


void test() {
    std::random_device rd;
    std::map<int, int> hist;
    std::uniform_int_distribution<int> dist(0, 9);
    for (int n = 0; n < 20000; ++n) {
        ++hist[dist(rd)]; // note: demo only: the performance of many
                          // implementations of random_device degrades sharply
                          // once the entropy pool is exhausted. For practical use
                          // random_device is generally only used to seed
                          // a PRNG such as mt19937
    }
    for (const auto & p : hist) {
        std::cout << p.first << " : " << std::string(p.second/100, '*') << '\n';
    }
}

void thread_task(std::atomic<bool> & boolean) {
//    std::default_random_engine engine{std::random_device{}()};
    std::mt19937 engine{std::random_device{}()};
    std::uniform_int_distribution<int64_t> dist{1000, 3000};
    int64_t wait_time = dist(engine);
    std::cout << "wait time:" << wait_time << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds{wait_time});
    std::string line = "Thread slept for " + std::to_string(wait_time) + "ms.\n";
    std::cout << line;
    boolean.store(true);
}

int main() {
    std::vector<std::thread> threads;
    std::atomic<bool> boolean{false};
    for(int i = 0; i < 4; i++) {
        threads.emplace_back([&]{thread_task(boolean);});
    }
    std::string line = "We reacted after a single thread finished!\n";
    while(!boolean) std::this_thread::yield();
    std::cout << line;
    for(std::thread & thread : threads) {
        thread.join();
    }

    test();
    return 0;
}
