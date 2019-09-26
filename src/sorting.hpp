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



#endif /*__SORTING_HPP*/
