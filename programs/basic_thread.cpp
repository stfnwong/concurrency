/* Basic thread management 
 *
 * From Chapter 2 of C++ Concurrency in Action
 */

#include <cstdio>
#include <thread>

#define LARGE_NUMBER 256
//#define WAIT_FOR_THREAD 

void do_something(const unsigned n)
{
    fprintf(stdout, "%d \n", n);
}

// A function that returns while a thread still has access to local variables 
struct func
{
    int &i;
    
    func(int &i_) : i(i_) {}

    void operator ()()      // note: why is this a functor in the examples?
    {
        for(unsigned j = 0; j < LARGE_NUMBER; j++)
            do_something(i);
    }
};

void oops(void)
{
    int some_local_state = 0;
    func test_func(some_local_state);

    std::thread test_thread(test_func);

#ifdef WAIT_FOR_THREAD
    test_thread.join();         // actually wait
#else
    test_thread.detach();       // WRECK IT
#endif /*WAIT_FOR_THREAD*/
}

// Who knows if thread is running by now...


int main(int argc, char *argv[])
{
    oops();
    fprintf(stdout, "Called oops()\n");
    return 0;
}
