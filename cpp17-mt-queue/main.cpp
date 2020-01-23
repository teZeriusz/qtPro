#include <thread>
#include <iostream>
#include <chrono>
#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <algorithm>


using namespace std::chrono_literals;
using std::vector;
using std::thread;
using std::unique_lock;
using std::mutex;
using std::condition_variable;
using std::queue;

class WorkQueue
{
    condition_variable m_work_available;
    mutex m_work_mutex;
    queue<int> m_work;

public:
    void push_work(int item)
    {
        unique_lock<mutex> lock(m_work_mutex);

        bool was_empty = m_work.empty();
        m_work.push(item);

        lock.unlock();

        if (was_empty)//XXX this if fail in MT
        {
            m_work_available.notify_one();
        }
  }

    int wait_and_pop()
    {
        unique_lock<mutex> lock(m_work_mutex);
        while (m_work.empty())
        {
            m_work_available.wait(lock);
        }//XXX can we that way?

        int tmp = m_work.front();
        m_work.pop();
        return tmp;
    }
};

int main() {
    WorkQueue work_queue;

    auto producer = [&]() {
        while (true) {
            work_queue.push_work(10);
            std::this_thread::sleep_for(2ms);
        }
    };

    vector<thread> producers;
    producers.push_back(std::thread(producer));
    producers.push_back(std::thread(producer));
    producers.push_back(std::thread(producer));
    producers.push_back(std::thread(producer));

    std::thread consumer([&]() {
    while (true)
        {
            int work_to_do = work_queue.wait_and_pop();
            std::cout << "Got some work: " << work_to_do << std::endl;
        }
    });

    std::for_each(producers.begin(), producers.end(), [](thread &p) {
        p.join();
    });

    consumer.join();
}
