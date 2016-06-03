extern "C"
{
#include "BitManip.h"
#include <stdint.h>
}

#include "Test_BitManip.h"
#include "CppUTest/TestHarness.h"


#define EIGHT_BITS (1<<7) | (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0)

// This is an experiment to help make it easier to figure out bit shifts.
// It looks crazy at first but it's nice when you get used to it.
#define B0000_0000 0x00
#define B0000_0001 0x01
#define B0000_0011 0x03
#define B0000_0101 0x05
#define B0000_1001 0x09
#define B0000_1111 0x0f
#define B0001_1000 0x18
#define B0011_0000 0x30
#define B1000_0000 0x80
#define B1000_0001 0x81
#define B1001_0000 0x90
#define B1001_1001 0x99
#define B1111_0000 0xf0



TEST_GROUP(SetBitmask)
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

TEST(SetBitmask, ItCanSetAllBitsInABitmask)
{
    SET_BITMASK(eightBit, EIGHT_BITS);
    BYTES_EQUAL(EIGHT_BITS, eightBit);
}

TEST(SetBitmask, ItDoesNotClearAnyBitsInABitmask)
{
    eightBit = 0xff;
    SET_BITMASK(eightBit, 0x00);
    BYTES_EQUAL(0xff, eightBit);
}

TEST(SetBitmask, ItCanSetTheLeastSignificantBit)
{
    SET_BITMASK( eightBit, (1<<0) );
    BYTES_EQUAL(0x01, eightBit);
}

TEST(SetBitmask, ItCanSetTheMostSignificantBit)
{
    SET_BITMASK( eightBit, (1<<7) );
    BYTES_EQUAL(0x80, eightBit);
}

// IGNORE_TEST(SetBitmask, ThereIsNoProtectionForThis)
// {
    // SET_BITMASK( eightBit, (1<<8) );
    // BYTES_EQUAL(0x00, eightBit);
// }



TEST_GROUP(ClearBitmask)
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

TEST(ClearBitmask, ItCanClearAllBits)
{
    CLEAR_BITMASK(eightBit, EIGHT_BITS);
    BYTES_EQUAL(0x00, eightBit);
}

TEST(ClearBitmask, ItWillNotSetAnyBits)
{
    eightBit = 0;
    CLEAR_BITMASK(eightBit, EIGHT_BITS);
    BYTES_EQUAL(0x00, eightBit);
}

TEST(ClearBitmask, ItCanClearTheLeastSignificantBit)
{
    CLEAR_BITMASK(eightBit, (1<<0));
    BYTES_EQUAL(0xfe, eightBit);
}

TEST(ClearBitmask, ItCanClearTheMostSignificantBit)
{
    CLEAR_BITMASK(eightBit, (1<<7));
    BYTES_EQUAL(0x7f, eightBit);
}

// IGNORE_TEST(SetBitmask, ThereIsNoProtectionForThis)
// {
//     CLEAR_BITMASK( eightBit, (1<<8) );
//     BYTES_EQUAL(0xff, eightBit);
// }



TEST_GROUP(SetBitmaskTo)
{
    uint8_t eightBit;
    uint8_t bitsToSet;
    uint8_t bitmask;

    void setup()
    {
        eightBit = 0;
        bitsToSet = 0;
        bitmask = 0;
    }

    void teardown()
    {
    }
};

TEST(SetBitmaskTo, ItClearsBitsWithinTheBitmask)
{
    eightBit  = 0x0f;
    bitsToSet = 0x05;
    bitmask   = 0x0f;
    SET_BITMASK_TO(eightBit, bitsToSet, bitmask);
    BYTES_EQUAL(0x05, eightBit);
}



TEST_GROUP(FilterBitmask)
{
    uint8_t bitmask;
    uint8_t filter;

    void setup()
    {
        bitmask = 0;
        filter = 0;
    }

    void teardown()
    {
    }
};

TEST(FilterBitmask, OfHexZeroAndZeroReturnsZero)
{
    BYTES_EQUAL( 0x00, FILTER_BITMASK(bitmask, filter) );
}

TEST(FilterBitmask, SetMatchingBits)
{
    bitmask = 0xff;
    filter = 0xff;

    BYTES_EQUAL( 0xff, FILTER_BITMASK(bitmask, filter) );
}

TEST(FilterBitmask, ClearsUnmatchingBits)
{
    bitmask = 0xff;
    filter = 0x00;
    BYTES_EQUAL( 0x00, FILTER_BITMASK(bitmask, filter) );

    bitmask = 0x00;
    filter = 0xff;
    BYTES_EQUAL( 0x00, FILTER_BITMASK(bitmask, filter) );
}

TEST(FilterBitmask, SetAndClearsBits)
{
    bitmask = 0xa5;
    filter = 0xff;
    BYTES_EQUAL( 0xa5, FILTER_BITMASK(bitmask, filter) );

    bitmask = 0xff;
    filter = 0xa5;
    BYTES_EQUAL( 0xa5, FILTER_BITMASK(bitmask, filter) );
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



TEST_GROUP(ShiftAndSetBitmaskTo)
{
    uint8_t eightBit;
    uint8_t bitsToSet;
    uint8_t bitmaskRange;
    uint8_t expected;

    void setup()
    {
        eightBit = 0;
        bitsToSet = 0;
        bitmaskRange = 0;
        expected = 0;
    }

    void teardown()
    {
    }
};

TEST(ShiftAndSetBitmaskTo, SetNothing)
{
    bitsToSet    = B0000_0000;
    bitmaskRange = B0000_0000;
    expected     = B0000_0000;
    SHIFT_AND_SET_BITMASK_TO(eightBit, bitsToSet, bitmaskRange);
    BYTES_EQUAL( expected, eightBit );
}

TEST(ShiftAndSetBitmaskTo, SetLeastSignifantBit)
{
    bitsToSet    = B0000_0001;
    bitmaskRange = B0000_0001;
    expected     = B0000_0001;
    SHIFT_AND_SET_BITMASK_TO(eightBit, bitsToSet, bitmaskRange);
    BYTES_EQUAL( expected, eightBit );
}

TEST(ShiftAndSetBitmaskTo, SetMostSignifantBit)
{
    bitsToSet    = B0000_0001;
    bitmaskRange = B1000_0000;
    expected     = B1000_0000;
    SHIFT_AND_SET_BITMASK_TO(eightBit, bitsToSet, bitmaskRange);
    BYTES_EQUAL( expected, eightBit );
}

TEST(ShiftAndSetBitmaskTo, SetSeveralBits)
{
    bitsToSet    = B0000_0011;
    bitmaskRange = B0011_0000;
    expected     = B0011_0000;
    SHIFT_AND_SET_BITMASK_TO(eightBit, bitsToSet, bitmaskRange);
    BYTES_EQUAL( expected, eightBit );
}

TEST(ShiftAndSetBitmaskTo, SetNonConsecutiveBits)
{
    bitsToSet    = B0000_1001;
    bitmaskRange = B1111_0000;
    expected     = B1001_0000;
    SHIFT_AND_SET_BITMASK_TO(eightBit, bitsToSet, bitmaskRange);
    BYTES_EQUAL( expected, eightBit );
}

TEST(ShiftAndSetBitmaskTo, ClearBitsWithinBitmaskRange)
{
    eightBit     = B0000_1111;
    bitsToSet    = B0000_0101;
    bitmaskRange = B0000_1111;
    expected     = B0000_0101;
    SHIFT_AND_SET_BITMASK_TO(eightBit, bitsToSet, bitmaskRange);
    BYTES_EQUAL( expected, eightBit );
}

TEST(ShiftAndSetBitmaskTo, DoNotAlterVariableOutsideOfBitmask)
{
    eightBit     = B1000_0001;
    bitsToSet    = B0000_0011;
    bitmaskRange = B0001_1000;
    expected     = B1001_1001;
    SHIFT_AND_SET_BITMASK_TO(eightBit, bitsToSet, bitmaskRange);
    BYTES_EQUAL( expected, eightBit );
}

TEST(ShiftAndSetBitmaskTo, DoNotSetBitsOutsideOfBitmaskRange)
{
    eightBit     = B0000_0000;
    bitsToSet    = B0000_0011;
    bitmaskRange = B0000_0001;
    expected     = B0000_0001;
    SHIFT_AND_SET_BITMASK_TO(eightBit, bitsToSet, bitmaskRange);
    BYTES_EQUAL( expected, eightBit );
}
