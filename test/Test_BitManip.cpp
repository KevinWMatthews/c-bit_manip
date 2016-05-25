extern "C"
{
#include "BitManip.h"
#include <stdint.h>
}

#include "Test_BitManip.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(BitManip)
{
    uint8_t eightBit;

    void setup()
    {
        eightBit = 0;
    }

    void teardown()
    {
    }
};

TEST(BitManip, ItCanSetAllBitsInABitmask)
{
    SET_BITS(eightBit, 0xff);
    BYTES_EQUAL(0xff, eightBit);
}

TEST(BitManip, ItDoesNotClearAnyBitsInABitmask)
{
    eightBit = 0xff;
    SET_BITS(eightBit, 0x00);
    BYTES_EQUAL(0xff, eightBit);
}

TEST(BitManip, ItCanSetTheLeastSignificantBit)
{
    SET_BITS( eightBit, (1<<0) );
    BYTES_EQUAL(0x01, eightBit);
}

TEST(BitManip, ItCanSetTheMostSignificantBit)
{
    SET_BITS( eightBit, (1<<7) );
    BYTES_EQUAL(0x80, eightBit);
}

// IGNORE_TEST(BitManip, ThereIsNoProtectionForThis)
// {
    // SET_BITS( eightBit, (1<<8) );
    // BYTES_EQUAL(0x00, eightBit);
// }
