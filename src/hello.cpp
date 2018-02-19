/* Hello, Concurrent world 
 */

#include <iostream>
#include <thread>

void hello(void)
{
    std::cout << "Hello, Concurrent World" << std::endl;
}

int main(void)
{
    std::thread t(hello);
    t.join();

    return 0;
}
