#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>


template<typename T>
class threadsafe_queue {
private:
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
public:
    threadsafe_queue() = default;
    threadsafe_queue(threadsafe_queue const& other)
    {
        std::lock_guard<std::mutex> lk(other.mut);
        data_queue=other.data_queue;
    }
    void push(T new_value)
    {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }
    void wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        value=data_queue.front();
        data_queue.pop();
    }
    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }
    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return false;
        value=data_queue.front();
        data_queue.pop();
        return true;
    }
    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }
    bool empty() const//XXX this is needed?
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};
//-------------test--------------
template<typename Predicate>
void minimal_wait(std::unique_lock<std::mutex>& lk,Predicate pred){
    while(!pred()){
        lk.unlock();
        lk.lock();
    }
}
//-------------test/usage---------
struct data_chunk {

};

bool more_data_to_prepare();
data_chunk prepare_data();

void process(data_chunk);
bool is_last_chunk(data_chunk);


threadsafe_queue<data_chunk> data_queue;
void data_preparation_thread()
{
    while(more_data_to_prepare())
    {
        data_chunk const data=prepare_data();
        data_queue.push(data);
    }
}
void data_processing_thread()
{
    while(true)
    {
        data_chunk data;
        data_queue.wait_and_pop(data);
        process(data);
        if(is_last_chunk(data)) //TODO wtf is here?
            break;
    }
}
////-----test---11
//#include <future>
//#include <cassert>

//void test_concurrent_push_and_pop_on_empty_queue()
//{
//    threadsafe_queue<int> q;
//    std::promise<void> go,push_ready,pop_ready;
//    std::shared_future<void> ready(go.get_future());
//    std::future<void> push_done;
//    std::future<int> pop_done;
//    try
//    {
//        push_done=std::async(std::launch::async,
//                               [&q,ready,&push_ready]()
//                               {
//                                   push_ready.set_value();
//                                   ready.wait();
//                                   q.push(42);
//                               }
//                               );
//        pop_done=std::async(std::launch::async,
//                              [&q,ready,&pop_ready]()
//                              {
//                                  pop_ready.set_value();
//                                  ready.wait();
//                                  return q.pop();
//                              }
//                              );
//        push_ready.get_future().wait();
//        pop_ready.get_future().wait();
//        go.set_value();
//        push_done.get();
//        assert(pop_done.get()==42);
//        assert(q.empty());
//    }
//    catch(...)
//    {
//        go.set_value();
//        throw;
//    }
//}

int main() {

    return 0;
}
