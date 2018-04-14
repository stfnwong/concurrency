/* TEST_SORTER
 * Unit test for threaded sort implemenation
 *
 * Stefan Wong 2018
 */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>
// Unit under test 
#include "sorter.hpp"

// Test harness class 
class TestSorter : public ::testing::Test
{
    protected:
        TestSorter() {}
        virtual ~TestSorter() {}
        virtual void SetUp() {}
        virtual void TearDown() {}
        bool verbose = false;       // set to true for additional output 
        size_t enc_buffer_size = 4096;
};


TEST_F(TestSorter, test_init)
{
    // Get a new sorter object 
    Sorter<float> sort_test;
    unsigned int num_elements = 16;
    std::list<float> input_to_sort;

    float test_input[16] = {0.4342, 1.54, 45254.0, 4353.4, 4.2, 0.000432, 0.43, 0.443, 
                            1.222, 1.0, 10.0, 10.001, 245.1, 3.2, 3.14, 3.14141414141};
    //float correct_output[16] = 
    for(unsigned int n = 0; n < num_elements; n++)
        input_to_sort.push_back(test_input[n]);

    // TODO: put this back when promise bug is sorted
    //std::list<float> sorted_output = sort_test.do_sort(input_to_sort);

    fprintf(stdout, "Items (pre-sort):\n");
    for(int n : input_to_sort)
        fprintf(stdout, " %f ", n);
    //for(unsigned int n = 0; n < input_to_sort.size(); n++)
    //    fprintf(stdout, " %f ", input_to_sort[n]);

    //fprintf(stdout, "Items (post-sort):\n");
    //for(int n : sorted_output)
    //    fprintf(stdout, " %f ", n);
}




int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

