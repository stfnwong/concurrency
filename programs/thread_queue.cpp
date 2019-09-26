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
#include <iostream>

#include "thread_queue.hpp"

#define GLOBAL_MAX 640000


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
    std::cout << "[" << __func__ << "] data : " << data << std::endl;
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
        std::cout << "[" << __func__ << "] preparing data " << data_proc_count << std::endl;
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

    std::cout << "[" << __func__ << "] all work done." << std::endl;

    return 0;
}
