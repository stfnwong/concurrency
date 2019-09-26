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


TEST_F(TestSorting, test_sequential_quicksort)
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

    // Now try to sort the list 
    std::list<int> out_list = sequential_quicksort(input_list);

    int n = 0;
    std::cout << " idx   val " << std::endl;
    for(auto it = out_list.begin(); it != out_list.end(); it++)
    {
        std::cout << "[" << std::setw(4) << std::setfill(' ') << n << "] ";
        std::cout << *it << std::endl;
        n++;
    }
}



int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
