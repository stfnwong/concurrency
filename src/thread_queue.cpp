/* Thread safe queue 
 * From section 4.1.1
 *
 *
 */


// How to use a std::condition_variable to handle cases where we want 
// we want a thread that's waiting for work to sleep until there is 
// data to process?

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
// create threads to access the queue
#include <thread>
// I hate iostream
#include <cstdio>

#define GLOBAL_MAX 640000

template <typename T> class ThreadQueue
{
    private:
        mutable std::mutex q_mutex;
        std::queue <T> data_q;
        std::condition_variable data_cond;

    public:
        ThreadQueue() {}
        // copy ctor 
        ThreadQueue(const ThreadQueue& other)
        {
            std::lock_guard <std::mutex> lock(other.q_mutex);
            this->data_q = other.data_q;
        }
        ~ThreadQueue() {}
        // disallow assignment 
        ThreadQueue& operator=(const ThreadQueue&) = delete;

        void push(T data)
        {
            std::lock_guard <std::mutex> lock(this->q_mutex);
            this->data_q.push(data);
            this->data_cond.notify_one();
        }

        bool try_pop(T &data)
        {
            std::lock_guard <std::mutex> lock(this->q_mutex);
            if(this->data_q.empty())
                return false;
            data = this->data_q.front();
            this->data_q.pop();

            return true;
        }

        std::shared_ptr<T> try_pop(void)
        {
            std::lock_guard <std::mutex> lock(this->q_mutex);
            if(this->data_q.empty())
                return std::shared_ptr <T>();

            std::shared_ptr <T> res(std::make_shared<T> (this->data_q.front()));
            this->data_q.pop();

            return res;
        }

        // wait and pop will wait until there is data then pop
        void wait_and_pop(T &data)
        {
            std::unique_lock <std::mutex> lock(this->q_mutex);
            // TODO : Not familiar with the syntax here....?
            this->data_cond.wait(lock, [this]{return !this->data_q.empty();});      
            data = this->data_q.front();
            this->data_q.pop();
        }

        std::shared_ptr <T> wait_and_pop(void)
        {
            std::unique_lock <std::mutex> lock(this->q_mutex);
            this->data_cond.wait(lock, [this]{return !this->data_q.empty();});
            std::shared_ptr <T> res(std::make_shared <T> (this->data_q.front()));
            this->data_q.pop();

            return res;
        }

        bool empty(void) const
        {
            std::lock_guard <std::mutex> lock(this->q_mutex);
            return this->data_q.empty();
        }
};



ThreadQueue <int> data_q;
int global_n = 0;

int prepare_data(void)
{
    // This isn't safe at all, but for the purposes 
    // of this test its fine
    return global_n++;         
}

bool more_data_to_prepare(void)
{
    return (global_n <= GLOBAL_MAX) ? true : false;
}

bool is_last_chunk(const int data)
{
    return (data >= GLOBAL_MAX) ? true : false;
}

void process(int data)
{
    fprintf(stdout, "data : %d\n", data);
}

void data_preparation_thread(void)
{
    while(more_data_to_prepare())
    {
        int data = prepare_data();
        data_q.push(data);
    }
}

void data_processing_thread(void)
{
    int data_proc_count = 0;
    while(1)
    {
        fprintf(stdout, "Preparing data %d\n", data_proc_count);
        int data;
        data_q.wait_and_pop(data);
        process(data);
        if(is_last_chunk(data))
            break;

        data_proc_count++;
    }
}



int main(int argc, char *argv[])
{
    std::thread data_prep_thread(data_preparation_thread);
    std::thread data_proc_thread(data_processing_thread);

    data_prep_thread.join();
    data_proc_thread.join();

    fprintf(stdout, "All work done\n");

    return 0;
}
