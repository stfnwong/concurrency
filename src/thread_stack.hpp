/*
 * THREAD_STACK
 * A thread-safe stack 
 *
 * Stefan Wong 2019
 */

#ifndef __THREAD_STACK_HPP
#define __THREAD_STACK_HPP

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

    private:
        // delete assignment operator so the stack can't be assigned
        ThreadStack &operator=(const ThreadStack&) = delete;    

    public:
        ThreadStack() {}
        ThreadStack(const ThreadStack &other)
        {
            std::lock_guard <std::mutex> lock(other.mutex);
            this->data = other.data;
        }

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



#endif /*__THREAD_STACK_HPP*/
