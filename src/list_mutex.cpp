/* The 'protecting a list with a mutex example
 *
 */

#include <list>
#include <mutex>
#include <algorithm>
#include <string>

class SomeData
{
    int a;
    std::string b;

    public:
        void do_something(void);
};

void SomeData::do_something(void)
{
    for(unsigned n = 0; n < 8; n++)
        fprintf(stdout, "do_something cycle %d\n", n);
}

class DataWrapper
{
    private:
        SomeData data;
        std::mutex mutex;
    public:
        template <typename F> void process_data(F func)
        {
            std::lock_guard <std::mutex> lock(this->mutex);
            func(data);
        }
};

// instantiate some badly constrained data 
SomeData *unprotected_data;

void malicious_function(SomeData &protected_data)
{
    unprotected_data = &protected_data;
}

DataWrapper X;

void foo(void)
{
    X.process_data(malicious_function); // pass in something dangerous
    unprotected_data->do_something();         // unprotected access to protected data 
}


int main(int argc, char *argv[])
{
    foo();
    //for(unsigned n = 6; n < 32; n++)
    //    add_to_list(n);

    //for(unsigned n = 0; n < 32; n++)
    //    fprintf(stdout, "List %s contain %d\n", list_contains(n) ? "does" : "does not", n);

    return 0;
}
