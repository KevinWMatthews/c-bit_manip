extern "C"
{
#include "BitManip.h"
#include <stdint.h>
}

#include "Test_BitManip.h"
#include "CppUTest/TestHarness.h"

static uint8_t eightBit;

TEST_GROUP(SetBits)
{
    void setup()
    {
        eightBit = 0;
    }

    void teardown()
    {
    }
};

TEST(SetBits, ItCanSetAllBitsInABitmask)
{
    SET_BITS(eightBit, 0xff);
    BYTES_EQUAL(0xff, eightBit);
}

TEST(SetBits, ItDoesNotClearAnyBitsInABitmask)
{
    eightBit = 0xff;
    SET_BITS(eightBit, 0x00);
    BYTES_EQUAL(0xff, eightBit);
}

TEST(SetBits, ItCanSetTheLeastSignificantBit)
{
    SET_BITS( eightBit, (1<<0) );
    BYTES_EQUAL(0x01, eightBit);
}

TEST(SetBits, ItCanSetTheMostSignificantBit)
{
    SET_BITS( eightBit, (1<<7) );
    BYTES_EQUAL(0x80, eightBit);
}

// IGNORE_TEST(SetBits, ThereIsNoProtectionForThis)
// {
    // SET_BITS( eightBit, (1<<8) );
    // BYTES_EQUAL(0x00, eightBit);
// }



TEST_GROUP(RightMostBit)
{
    void setup()
    {
        eightBit = 0;
    }

    void teardown()
    {
    }
};

TEST(RightMostBit, ItReturnsZeroIfNoBitsAreSet)
{
    BYTES_EQUAL( 0, RIGHTMOST_BIT_NUMBER(0x00) );
}

TEST(RightMostBit, ItReturnsTheLeastSignificantBit)
{
    BYTES_EQUAL( 0, RIGHTMOST_BIT_NUMBER(0x01) );
}

TEST(RightMostBit, ItReturnsTheMostSignificantBit)
{
    BYTES_EQUAL( 7, RIGHTMOST_BIT_NUMBER(0x80) );
}

TEST(RightMostBit, ItReturnsTheRightMostBitIfSeveralBitsAreSet)
{
    BYTES_EQUAL( 3, RIGHTMOST_BIT_NUMBER(0xF8) );
}
