/*
 * SORTING
 * Various sort algorithms
 * 
 * Stefan Wong 2019
 */

#ifndef __SORTING_HPP
#define __SORTING_HPP


#include <memory>           // for std::shared_ptr
#include <algorithm>        // for std::partition
#include <list>
// for parallel implementation
#include <future>



/*
 * sequential_quicksort()
 * A templated sequential quick sort. This is actually supposed to implement an 
 * functional style recursive quick sort.
 */
template <typename T> std::list<T> sequential_quicksort(std::list<T> input)
{
    // Note that we aren't using a const ref at the top because input is going to get spliced later on
    if(input.empty())
        return input;


    std::list<T> result;
    // The book uses an iterator here. I hate C++ iterators.
    // So to get the pivot right here we just take the first element using splice() 
    // (that is, this function https://en.cppreference.com/w/cpp/container/list/splice). 
    //
    result.splice(result.begin(), input, input.begin());

    T const& pivot = *result.begin();       // more iterator stuff

    // even more iterators
    // Here we use a std::partition to divide the sequence into values that are less than 
    // the pivot (using a lambda with reference capturebe).
    // std::partition does an in-place re-arrangement of the data here.
    auto divide_point = std::partition(
            input.begin(),
            input.end(),
            [&](T const& t){ return t < pivot; }
    );

    // Because the point here is to use recursion, we need two 'halves' to sort.
    // The lower of the two halves is going to be whatever falls below the divide 
    // point. The upper part is whatever is left in 'input'.
    std::list<T> lower_list;
    lower_list.splice(
            lower_list.end(),
            input,
            input.begin(),
            divide_point
    );

    // here we do the actual recursive sort
    std::list<T> new_lower(sequential_quicksort(std::move(lower_list)));
    std::list<T> new_upper(sequential_quicksort(std::move(input)));

    // splice the output lists back together.
    result.splice(result.end(), new_upper);
    result.splice(result.begin(), new_lower);

    return result;
}




/*
 * parallel_quicksort()
 * A templated parallel quick sort. 
 */
template <typename T> std::list<T> parallel_quicksort(std::list<T> input)
{
    if(input.empty())
        return input;

    std::list<T> result;
    result.splice(
            result.begin(),
            input,
            input.begin()
    );

    // set the pivot point as in the sequential version
    T const& pivot = *result.begin();

    // NOTE: I think I actually want to see how this actually works... that is I want to see
    // what assembly structure one gets from a std::partition
    auto divide_point = std::partition(
            input.begin(),
            input.end(),
            [&](T const& t){ return t < pivot; }
    );

    std::list<T> lower_list;
    lower_list.splice(
            lower_list.end(), 
            input,
            input.begin(),
            divide_point
    );

    // Before we sorted recursively in the same thread. This time we do the sorting for 
    // the lower part of the list in a new thread using std::async. The upper portion of
    // the list is sorted 'directly' (that is, in the same thread) as before.
    std::future<std::list<T>> new_lower(    
            std::async(&parallel_quicksort<T>, std::move(lower_list))
    );

    // Same as previous, where the upper part of the sort is done in the same thread
    auto new_higher(
            parallel_quicksort(std::move(input))
    ) ;


    // splice all the sub-lists together into a single list
    result.splice(result.end(), new_higher);
    // NOTE here about get()
    // Because of the call to std::async above, the type of new_lower is in fact 
    // std::future<std::list<T>> rather than just std::list<T>. Therefore we need to 
    // call get() to actually retrieve the value (https://en.cppreference.com/w/cpp/thread/future/get)
    result.splice(result.begin(), new_lower.get());

    return result;
}



#endif /*__SORTING_HPP*/
