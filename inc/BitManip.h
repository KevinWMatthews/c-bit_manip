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

// A wrapper for the standard bitwise operation.
#define BITWISE_AND(bitmask1, bitmask2) ((bitmask1) & (bitmask2))

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
#define SHIFT_AND_SET_BITMASK(variable, bitsToSet, bitmaskRange) \
    ( SET_BITMASK(variable, \
                BITWISE_AND(bitmaskRange, \
                    SHIFT_BITMASK(bitsToSet, bitmaskRange))) )



//Check if a single bit is set, given by a bitmask.
//To check multiple bits, use IF_BITMASK.
//Evaluates to 1 if true and 0 if false.
#define IF_BIT(variable, bit) (1 && BITWISE_AND(variable, bit))

//Check if a signel bit is set, given by a bit number.
#define IF_BIT_NUMBER(variable, bitNumber) (1 && BITWISE_AND(1<<(bitNumber), variable))

//Compare sections of two bitmasks.
#define IF_BITMASK(expectedBitmask, actualBitmask, bitsToCheck) \
  ( ((bitsToCheck) != 0) && \
    (BITWISE_AND(expectedBitmask, bitsToCheck) == BITWISE_AND(actualBitmask, bitsToCheck)) )

//Set a single bit given by a bit number.
//This macro will not clear bits.
#define SET_BIT_NUMBER(variable, bitNumber) ((variable) |= (1<<(bitNumber)))

//Set and clear bits in variable so they match the new value
#define SET_BITMASK_TO(variable, newValue, bitsToSet) \
{ \
  CLEAR_BITMASK(variable, bitsToSet); \
  SET_BITMASK(variable, BITWISE_AND(newValue, bitsToSet)); \
}

//Set and clear bits in variable so they match the new value
//Use this when the new value needs to be bit shifted.
//For example, set the bits 4 to 7 to 0x55 with
// SHIFT_AND_SET_BITMASK_TO(variable, 0x55, 0xf0)
//Bitmask must be of consecutive bits!
#define SHIFT_AND_SET_BITMASK_TO(variable, newValue, bitsToSet) \
{ \
  CLEAR_BITMASK(variable, bitsToSet); \
  SET_BITMASK(variable, BITWISE_AND((newValue) << RIGHTMOST_BIT_NUMBER(bitsToSet), bitsToSet)); \
}


//Clear a single bit given by a bit number
#define CLEAR_BIT_NUMBER(variable, bitNumber) ((variable) &= ~(1<<(bitNumber)))

//This is GCC specific!
//The compiler's return value is 1-indexed.
//I return a 0-indexed value that can be used directly for bitshifting.
//Manually return 0 if the bitmask is 0.
#define RIGHTMOST_BIT_NUMBER(bitmask) ((bitmask) == 0 ? 0 : __builtin_ffs(bitmask) - 1)



#endif
