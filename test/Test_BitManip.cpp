extern "C"
{
#include "BitManip.h"
}

#include "Test_BitManip.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(BitManip)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(BitManip, ItCanFail)
{
    FAIL("flunk")
}
