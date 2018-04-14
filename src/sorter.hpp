/* SORTER
 * Parallel sorting objects. Taken from "C++ Concurrency in Action"
 *
 * Stefan Wong 2018.
 */

#ifndef __SORTER_HPP
#define __SORTER_HPP

#include <vector>
#include <list>
#include <future>
#include <thread>
#include <chrono>
#include <memory>           // for std::shared_ptr
#include <algorithm>        // for std::partition
// Other modules from this experiment
#include "thread_stack.hpp"

template <typename T>
class Sorter
{
    /*
    // a chunk of data to sort
    struct Chunk
    {
        std::list<T> data;
        std::promise<std::list<T>> promise;
    };
    
    // data stack
    ThreadStack<Chunk> chunks;
    std::vector <std::thread> threads;
    const unsigned max_thread_count;
    std::atomic<bool> data_end;     // true when all chunks are sorted

    public:
        // ctor 
        Sorter() : max_thread_count(std::thread::hardware_concurrency() - 1), data_end(false) {}

        // dtor
        ~Sorter()
        {
            this->data_end = true;
            for(unsigned int i = 0; i < this->threads.size(); i++)
                this->threads[i].join();
        }

        void try_sort_chunk(void)
        {
            std::shared_ptr <Chunk> chunk = this->chunks.pop();
            if(chunk)
                this->sort_chunk(chunk);
        }

        void sort_chunk(const std::shared_ptr<Chunk>& chunk)
        {
            chunk->promise.set_value(this->do_sort(chunk->data));
        }

        std::list<T> do_sort(std::list<T> & chunk_data)
        {
            if(chunk_data.empty())
                return chunk_data;

            // Partition the data 
            std::list<T> result;
            result.splice(result.begin(), chunk_data, chunk_data.begin());
            const T& partition_val = *result.begin();

            // start creating the positions where the work load will be divided 
            typename std::list<T>::iterator divide_point = 
                std::partition(chunk_data.begin(), chunk_data.end(), 
                        [&](const T& val){ return val < partition_val;});


            Chunk new_lower_chunk;
            new_lower_chunk.data.splice(new_lower_chunk.data.end(),
                    chunk_data,
                    chunk_data.begin(),
                    divide_point);

            std::future<std::list<T>> new_lower = new_lower_chunk.promise.get_future();
            this->chunks.push(std::move(new_lower_chunk));

            if(this->threads.size() < this->max_thread_count)
            {
                this->threads.push_back(std::thread(&Sorter<T>::sort_thread, this));
            }

            std::list<T> new_higher(do_sort(chunk_data));
            result.splice(result.end(), new_higher);
            while(new_lower.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
                this->try_sort_chunk();

            result.splice(result.begin(), new_lower.get());
            return result;
        }

        void sort_thread(void)
        {
            while(!this->data_end)
            {
                this->try_sort_chunk();
                std::this_thread::yield();
            }
        }
        */

};


#endif /*__SORTER_HPP*/
