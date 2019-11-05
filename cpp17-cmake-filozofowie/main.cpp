#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>
#include "fmt/format.h"

using namespace std;

//mutex status_mutex;

// Każdy filozof działa we własnym wątku.
class DiningPhilosophers;
class Philosopher {
    size_t id;
    size_t fork1;
    size_t fork2;
    DiningPhilosophers * const diningPhilosophers;

public:
    Philosopher(size_t _id, size_t _fork1, size_t _fork2, DiningPhilosophers * const dphil):
        id(_id), fork1(_fork1), fork2(_fork2), diningPhilosophers(dphil) {
    }

    [[noreturn]]
    void operator()() {
        run();
    }

    [[noreturn]]
    void run();

    void status(string msg) {
//        lock_guard<mutex> lock(status_mutex);
        cout << fmt::format("Filozof {}: {}\n", id, msg );
    }
};

class DiningPhilosophers {
// Każdy „widelec” jest tylko obiektem typu mutex, na którym wykonujemy synchronizację.
    vector<std::unique_ptr<mutex>> forks;
    vector<Philosopher> philosophers;
    vector<thread> threads;

    friend class Philosopher;

// Przygotowuje widelce i filozofów.
public:
    DiningPhilosophers(size_t num){
        for(size_t i = 0; i < num; ++i) {
            size_t fork1 = i;
            size_t fork2 = ( i + 1 ) % num;

            if ( ( i % 2 ) == 0 ){
                philosophers.emplace_back(i, fork2, fork1, this);
            } else {
                philosophers.emplace_back(i, fork1, fork2, this);
            }
            forks.emplace_back(make_unique<mutex>());
        }
    }

    void operator()() {
        startEating();
    }

    // Uruchamia proces jedzenia.
    void startEating() {
        for(size_t i = 0; i < philosophers.size(); i++) {
            threads.emplace_back(philosophers[i]);
//             threads[i].join();
        }
        for(size_t i = 0; i < philosophers.size(); i++) {
//            threads.emplace_back(philosophers[i]);
            threads[i].join();
        }
    }

};
// Punkt początkowy symulacji.

[[noreturn]]
void Philosopher::run() {
    status(fmt::format("Gotowy do jedzenia przy użyciu widelców {} i {}", fork1, fork2));
    while ( true ){
        status(fmt::format("Podnoszenie widelca {}", fork1));
        {
            lock_guard<mutex> f1(*(diningPhilosophers->forks[fork1]));
                status( fmt::format("Podnoszenie widelca {}", fork2));

            {
                lock_guard<mutex> f2(*(diningPhilosophers->forks[fork2]));
                status("Jedzenie");
            }
        }
    }
}
int main() {
    DiningPhilosophers d(5);
    d.startEating();
    return 0;
}
