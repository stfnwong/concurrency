/* TEST_LOCK_FREE_STACK
 * Unit test for threaded sort implemenation
 *
 * Stefan Wong 2018
 */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>
// Unit under test 
#include "lock_free_stack.hpp"

// Test harness class 
class TestLockFreeStack : public ::testing::Test
{
    protected:
        TestLockFreeStack() {}
        virtual ~TestLockFreeStack() {}
        virtual void SetUp() {}
        virtual void TearDown() {}
        bool verbose = false;       // set to true for additional output 
        size_t enc_buffer_size = 4096;
};

TEST_F(TestLockFreeStack, test_init)
{
    LockFreeStack<float> lfs;
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
