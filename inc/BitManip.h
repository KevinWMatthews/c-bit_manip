#ifndef __BitManip_H
#define __BitManip_H



// Multi-statement macros cannot be rvalues or be placed within parenthesis!!
// Bit numbers are zero-indexed.

// Set one or several bits given by a bitmask.
// This macro will not clear bits.
#define SET_BITMASK(variable, bitmask) ((variable) |= (bitmask))

// Clear one or several bits given by a bitmask.
// This macro will not set bits
#define CLEAR_BITMASK(variable, bitmask) ((variable) &= ~(bitmask))

// Set AND clear bits in given by a bitmask
#define SET_BITMASK_TO(variable, bitsToSet, bitmask) \
{ \
    CLEAR_BITMASK(variable, bitmask); \
    SET_BITMASK(variable, FILTER_BITMASK(bitsToSet, bitmask)); \
}



// A wrapper for the standard bitwise and operation.
// Filter out/unset bits that don't belong in a bitmask.
// The filter and bitmask are actually interchangeable.
// I'm experimenting with this macro name to see if it improves readability.
#define FILTER_BITMASK(bitmask, filter) ((bitmask) & (filter))

// Set desired bits in a bitmask.
// For example, to set bits 5 and 6 in the bitmask range 0xF0, let:
//   bitsToSet = 0x06 (0b0110)
//   bitmaskRange = (1<<7) | (1<<6) | (1<<5) | (1<<4)
// The macro will take bitsToSet and shift it so that it lines up with the bitmaskRange.
#define SHIFT_BITMASK(bitsToSet, bitmaskRange) ( (bitsToSet) << RIGHTMOST_BIT_NUMBER(bitmaskRange) )



// This is complicated but very useful: :/
//   First shift the bits to set into the bitmask range.
//   Then filter the bits to set using a bitwise and.
//   Then set the bits in the variable.
// This is not a function so that we can avoid providing a specific data type for the arguments.
#define SHIFT_AND_SET_BITMASK_TO(variable, bitsToSet, bitmaskRange) \
    { \
      CLEAR_BITMASK(variable, bitmaskRange); \
      SET_BITMASK(variable, \
                FILTER_BITMASK( SHIFT_BITMASK(bitsToSet, bitmaskRange), bitmaskRange) ); }



//Check if a single bit is set, given by a bitmask.
//To check multiple bits, use IF_BITMASK.
//Evaluates to 1 if true and 0 if false.
#define IF_BIT(variable, bit) (1 && FILTER_BITMASK(variable, bit))

//Check if a signel bit is set, given by a bit number.
#define IF_BIT_NUMBER(variable, bitNumber) (1 && FILTER_BITMASK(1<<(bitNumber), variable))

//Compare sections of two bitmasks.
#define IF_BITMASK(expectedBitmask, actualBitmask, bitsToCheck) \
  ( ((bitsToCheck) != 0) && \
    (FILTER_BITMASK(expectedBitmask, bitsToCheck) == FILTER_BITMASK(actualBitmask, bitsToCheck)) )

//Set a single bit given by a bit number.
//This macro will not clear bits.
#define SET_BIT_NUMBER(variable, bitNumber) ((variable) |= (1<<(bitNumber)))

//Clear a single bit given by a bit number
#define CLEAR_BIT_NUMBER(variable, bitNumber) ((variable) &= ~(1<<(bitNumber)))

//This is GCC specific!
//The compiler's return value is 1-indexed.
//I return a 0-indexed value that can be used directly for bitshifting.
//Manually return 0 if the bitmask is 0.
#define RIGHTMOST_BIT_NUMBER(bitmask) ((bitmask) == 0 ? 0 : __builtin_ffs(bitmask) - 1)



#endif
