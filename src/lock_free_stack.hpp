/* LOCK FREE STACK IMPLEMENTATION
 * Taken/adapted from Listing 7.2, 
 * C++ Concurrency in action
 *
 * Stefan Wong 2018
 */

#ifndef __LOCK_FREE_STACK_HPP
#define __LOCK_FREE_STACK_HPP

#include <atomic>

template <typename T> class LockFreeStack
{
    public:
        struct node
        {
            T data;
            node* next;
            node(const T* d) : data(d) {} 
        };

        std::atomic<node*> head;

    public:
        void push(const T& data)
        {
            const node* new_node = new node(data);
            new_node->next = this->head.load();
            // Set the head pointer to the new node
            while(!this->head.compare_exchange_weak(new_node->next, new_node));
        }

        void pop(T& result)
        {
            node* old_head = this->head.load();
            while(!this->head.compare_exchange_weak(old_head, old_head->next));
            result = old_head->data;
        }
};

#endif /*__LOCK_FREE_STACK_HPP*/
