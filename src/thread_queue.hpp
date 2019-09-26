/*
 * THREAD_QUEUE
 * A threaded queue (from section 4.1.1)
 *
 * Stefan Wong 2019
 */

#ifndef __THREAD_QUEUE_HPP
#define __THREAD_QUEUE_HPP


#include <queue>
#include <mutex>
#include <condition_variable>


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


#endif /*__THREAD_QUEUE_HPP*/
