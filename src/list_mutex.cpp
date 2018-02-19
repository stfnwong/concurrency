/* The 'protecting a list with a mutex example
 *
 */

#include <list>
#include <mutex>
#include <algorithm>

// globals here for sake of example 
std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(new_value);
    // note: when do we unlock the mutex?
}

bool list_contains(int value_to_find)
{
    std::lock_guard <std::mutex> guard(some_mutex);
    return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

int main(int argc, char *argv[])
{
    for(unsigned n = 6; n < 32; n++)
        add_to_list(n);

    for(unsigned n = 0; n < 32; n++)
        fprintf(stdout, "List %s contain %d\n", list_contains(n) ? "does" : "does not", n);

    return 0;
}
