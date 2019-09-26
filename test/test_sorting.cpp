/* TEST_SORTING
 * Tests for various sort algorithms 
 *
 * Stefan Wong 2019
 */

#include <list>
#include <iostream>
#include <gtest/gtest.h>

// Unit under test 
#include "sorting.hpp"


// undefine this for profiling (as it removes character stream stuff)
//#define PRINT_OUTPUT


// Test harness class 
class TestSorting : public ::testing::Test
{
    protected:
        TestSorting() {}
        virtual ~TestSorting() {}
        virtual void SetUp() {}
        virtual void TearDown() {}
        bool verbose = false;       // set to true for additional output 
};


std::list<int> create_test_list(void)
{
    std::list<int> input_list;

    // get some junk to put in the list 
    input_list.push_back(108);
    input_list.push_back(8);
    input_list.push_back(453543);
    input_list.push_back(42);
    input_list.push_back(29);
    input_list.push_back(3);
    input_list.push_back(34);
    input_list.push_back(9);
    input_list.push_back(32843);
    input_list.push_back(4352);
    input_list.push_back(98);
    input_list.push_back(423);
    input_list.push_back(1654);
    input_list.push_back(326);
    input_list.push_back(54);
    input_list.push_back(33);
    input_list.push_back(132);

    return input_list;
}

std::list<int> create_ref_list(void)
{
    std::list<int> ref_list;
    ref_list.push_back(3);
    ref_list.push_back(8);
    ref_list.push_back(9);
    ref_list.push_back(29);
    ref_list.push_back(33);
    ref_list.push_back(34);
    ref_list.push_back(42);
    ref_list.push_back(54);
    ref_list.push_back(98);
    ref_list.push_back(108);
    ref_list.push_back(132);
    ref_list.push_back(326);
    ref_list.push_back(423);
    ref_list.push_back(1654);
    ref_list.push_back(4352);
    ref_list.push_back(32843);
    ref_list.push_back(453543);

    return ref_list;
}


TEST_F(TestSorting, test_sequential_quicksort)
{
    std::list<int> input_list = create_test_list();

    // Now try to sort the list 
    std::list<int> out_list = sequential_quicksort(input_list);

#ifdef PRINT_OUTPUT
    int n = 0;
    std::cout << " idx   val " << std::endl;
    for(auto it = out_list.begin(); it != out_list.end(); it++)
    {
        std::cout << "[" << std::setw(4) << std::setfill(' ') << n << "] ";
        std::cout << *it << std::endl;
        n++;
    }
#endif /*PRINT_OUTPUT*/

    // get a reference list to compare against
    std::list<int> ref_list = create_ref_list();
    
    // Check that the list actually was sorted
    ASSERT_EQ(ref_list.size(), out_list.size());
    // use a gaggle of iterators here
    std::list<int>::iterator ref_it = ref_list.begin();
    std::list<int>::iterator test_it = out_list.begin();


    for( ; ref_it != ref_list.end() && test_it != out_list.end(); ++ref_it, ++test_it)
    {
        ASSERT_EQ(*ref_it, *test_it);
    }
}

TEST_F(TestSorting, test_parallel_quicksort)
{
    std::list<int> input_list = create_test_list();

    // Now try to sort the list 
    std::list<int> out_list = parallel_quicksort(input_list);

#ifdef PRINT_OUTPUT
    int n = 0;
    std::cout << " idx   val " << std::endl;
    for(auto it = out_list.begin(); it != out_list.end(); it++)
    {
        std::cout << "[" << std::setw(4) << std::setfill(' ') << n << "] ";
        std::cout << *it << std::endl;
        n++;
    }
#endif /*PRINT_OUTPUT*/

    // get a reference list to compare against
    std::list<int> ref_list = create_ref_list();

    // Check that the list actually was sorted
    ASSERT_EQ(ref_list.size(), out_list.size());
    // use a gaggle of iterators here
    std::list<int>::iterator ref_it = ref_list.begin();
    std::list<int>::iterator test_it = out_list.begin();


    for( ; ref_it != ref_list.end() && test_it != out_list.end(); ++ref_it, ++test_it)
    {
        ASSERT_EQ(*ref_it, *test_it);
    }
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
