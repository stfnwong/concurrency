/* Thread safe stack
 *
 * From listing 3.4
 */


#include <exception>
#include <memory>
#include <mutex>
#include <stack>

#include <iostream>

// Thread stack implementation now here
#include "thread_stack.hpp"


int main(int argc, char *argv[])
{
    // This is just a very basic instantiation that doesn't really test
    // the limits of this stack (eg: there are no threads at this time)
    ThreadStack<int> test_stack;

    for(int n = 50; n < 150; n++)
        test_stack.push(n);

    int pop_value;
    while(!test_stack.empty())
    {
        test_stack.pop(pop_value);
        std::cout << "popped " << pop_value << std::endl;
    }

    return 0;
}
