/* TEST_SORTER
 * Unit test for threaded sort implemenation
 *
 * Stefan Wong 2018
 */



#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>


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

}




int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

