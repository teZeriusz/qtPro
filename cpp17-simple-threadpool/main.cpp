#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <chrono>


/// \brief Use this class to run tasks in parallel.
class ThreadPool {
public:
    ThreadPool() = delete;
    ThreadPool( size_t threads );
    ~ThreadPool();

    /// \brief Initialize the ThreadPool with a number of threads.
    /// This method does nothing if the thread pool is already running,
    /// i.e. ThreadPool( size_t ) was called.
    void initializeWithThreads( size_t threads );

    /// \brief Schedule a task to be executed by a thread immediately.
    void schedule( const std::function<void()>& );

    /// \brief a blocking function that waits until the threads have processed all the tasks in the queue.
    void wait() const;

private:
    std::vector<std::thread>            m_workers;
    std::queue<std::function<void()>>   m_taskQueue;
    std::atomic_uint                    m_taskCount{0u};
    std::mutex                          m_mutex;
    std::condition_variable             m_condition;
    std::atomic_bool                    m_stop{false};
};

ThreadPool::ThreadPool(size_t threads) {
    initializeWithThreads( threads );
}

ThreadPool::~ThreadPool() {
    m_stop = true;
    m_condition.notify_all();
    for ( std::thread& w: m_workers ) {
        w.join();
    }
}

void ThreadPool::initializeWithThreads( size_t threads ) {
    for ( size_t i = 0; i < threads; i++ ) {
        //each thread executes this lambda
        m_workers.emplace_back( [this]() -> void {
            while (true) {
                std::function<void()> task;
                {   //acquire lock
                    std::unique_lock<std::mutex> lock( m_mutex );
                    m_condition.wait( lock, [this]() -> bool {
                        return !m_taskQueue.empty() || m_stop;
                    });

                    if ( m_stop && m_taskQueue.empty() ) {
                        return;
                    }

                    task = std::move( m_taskQueue.front() );
                    m_taskQueue.pop();
                }   //release lock
                task();
                m_taskCount--;
            }   //while
        });
    }   //for
}

void ThreadPool::schedule( const std::function<void()>& task ) {
    {
        std::unique_lock<std::mutex> lock( m_mutex );
        m_taskQueue.push( task );
    }
    m_taskCount++;
    m_condition.notify_one();
}

void ThreadPool::wait() const {
    while ( m_taskCount != 0u ) {
        std::this_thread::sleep_for( std::chrono::microseconds(1) );
    }
}

#include <iostream>
int main()
{
//    ThreadPool tp(5);
//    std::string ss("ala ma kota a kot ma ale");
//    tp.initializeWithThreads(3);
//    std::cout << "ss:" << ss;
    return 0;
}
