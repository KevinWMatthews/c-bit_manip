extern "C"
{
#include "BitManip.h"
#include <stdint.h>
}

#include "Test_BitManip.h"
#include "CppUTest/TestHarness.h"


#define EIGHT_BITS (1<<7) | (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0)



TEST_GROUP(SetBits)
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

TEST(SetBits, ItCanSetAllBitsInABitmask)
{
    SET_BITS(eightBit, EIGHT_BITS);
    BYTES_EQUAL(EIGHT_BITS, eightBit);
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



TEST_GROUP(ClearBits)
{
    uint8_t eightBit;

    void setup()
    {
        eightBit = 0xff;
    }

    void teardown()
    {
    }
};

TEST(ClearBits, ItCanClearAllBits)
{
    CLEAR_BITS(eightBit, EIGHT_BITS);
    BYTES_EQUAL(0x00, eightBit);
}

TEST(ClearBits, ItWillNotSetAnyBits)
{
    eightBit = 0;
    CLEAR_BITS(eightBit, EIGHT_BITS);
    BYTES_EQUAL(0x00, eightBit);
}

TEST(ClearBits, ItCanClearTheLeastSignificantBit)
{
    CLEAR_BITS(eightBit, (1<<0));
    BYTES_EQUAL(0xfe, eightBit);
}

TEST(ClearBits, ItCanClearTheMostSignificantBit)
{
    CLEAR_BITS(eightBit, (1<<7));
    BYTES_EQUAL(0x7f, eightBit);
}

// IGNORE_TEST(SetBits, ThereIsNoProtectionForThis)
// {
//     CLEAR_BITS( eightBit, (1<<8) );
//     BYTES_EQUAL(0xff, eightBit);
// }



TEST_GROUP(BitwiseAnd)
{
    uint8_t bitmask1;
    uint8_t bitmask2;

    void setup()
    {
        bitmask1 = 0;
        bitmask2 = 0;
    }

    void teardown()
    {
    }
};

TEST(BitwiseAnd, OfHexZeroAndZeroReturnsZero)
{
    BYTES_EQUAL( 0x00, BITWISE_AND(bitmask1, bitmask2) );
}

TEST(BitwiseAnd, SetMatchingBits)
{
    bitmask1 = 0xff;
    bitmask2 = 0xff;

    BYTES_EQUAL( 0xff, BITWISE_AND(bitmask1, bitmask2) );
}

TEST(BitwiseAnd, ClearsUnmatchingBits)
{
    bitmask1 = 0x00;
    bitmask2 = 0xff;
    BYTES_EQUAL( 0x00, BITWISE_AND(bitmask1, bitmask2) );

    bitmask1 = 0xff;
    bitmask2 = 0x00;
    BYTES_EQUAL( 0x00, BITWISE_AND(bitmask1, bitmask2) );
}

TEST(BitwiseAnd, SetAndClearsBits)
{
    bitmask1 = 0xff;
    bitmask2 = 0xa5;
    BYTES_EQUAL( 0xa5, BITWISE_AND(bitmask1, bitmask2) );

    bitmask1 = 0xa5;
    bitmask2 = 0xff;
    BYTES_EQUAL( 0xa5, BITWISE_AND(bitmask1, bitmask2) );
}



TEST_GROUP(RightMostBit)
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



TEST_GROUP(ShiftBitmask)
{
    uint8_t bitsToSet;
    uint8_t bitmaskRange;

    void setup()
    {
        bitsToSet = 0;
        bitmaskRange = 0;
    }

    void teardown()
    {
    }
};

TEST(ShiftBitmask, ItCanHandleZeroBitmask)
{
    BYTES_EQUAL( 0x00, SHIFT_BITMASK(bitsToSet, bitmaskRange) );
}

TEST(ShiftBitmask, ItCanShiftToMinimum)
{
    bitsToSet = 0x01;
    bitmaskRange = 0x01;
    BYTES_EQUAL( 0x01, SHIFT_BITMASK(bitsToSet, bitmaskRange) );
}

TEST(ShiftBitmask, ItCanShiftToMaximum)
{
    bitsToSet = 0x01;
    bitmaskRange = 0x80;
    BYTES_EQUAL( 0x80, SHIFT_BITMASK(bitsToSet, bitmaskRange) );
}

TEST(ShiftBitmask, ItCanShiftSeveralBits)
{
    bitsToSet = 0x03;
    bitmaskRange = 0x30;
    BYTES_EQUAL( 0x30, SHIFT_BITMASK(bitsToSet, bitmaskRange) );
}

TEST(ShiftBitmask, ItCanShiftSomeBits)
{
    bitsToSet = 0x06;
    bitmaskRange = 0xf0;
    BYTES_EQUAL( 0x60, SHIFT_BITMASK(bitsToSet, bitmaskRange) );
}
