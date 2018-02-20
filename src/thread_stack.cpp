/* Thread safe stack
 *
 * From listing 3.4
 */


#include <exception>
#include <memory>
#include <mutex>
#include <stack>

// Exception for stack 
struct empty_stack: std::exception
{
    const char *what() const throw()
    {
        return "Stack is empty!\n";
    }
};


// Outline of a thread safe stack 
// This is really just a wrapper around std::stack
//
template <typename T> class ThreadStack
{
    private:
        std::stack <T> data;
        mutable std::mutex mutex;

    public:
        ThreadStack() {}
        ThreadStack(const ThreadStack &other)
        {
            std::lock_guard <std::mutex> lock(other.mutex);
            this->data = other.data;
        }
        // delete assignment operator so the stack can't be assigned
        ThreadStack &operator=(const ThreadStack&) = delete;    

        // Push element 
        void push(T value)
        {
            // NOTE: std::lock_guard automatically unwinds at end of 
            // scope (when we exit this stack frame)
            std::lock_guard <std::mutex> lock(this->mutex);
            this->data.push(value);
        }

        // get reference to top element
        std::shared_ptr<T> pop(void)
        {
            std::lock_guard <std::mutex> lock(this->mutex);
            if(this->data.empty())
                throw empty_stack();        // check for empty before trying to pop value
            
            // Allocate return value before modifying stack 
            std::shared_ptr <T> const res(std::make_shared<T> (this->data.top()));
            this->data.pop();

            return res;
        }

        // Pop into reference
        void pop(T &value)
        {
            std::lock_guard <std::mutex> lock(this->mutex);

            if(this->data.empty())
                throw empty_stack();
            value = this->data.top();
            this->data.pop();
        }

        bool empty(void) const
        {
            std::lock_guard<std::mutex> lock(this->mutex);
            return this->data.empty();
        }
};



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
        fprintf(stdout, "popped %d\n", pop_value);
    }

    return 0;
}
