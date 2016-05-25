#ifndef __BitManip_H
#define __BitManip_H

// Set a single or several bits given by a bitmask.
// This macro will not clear bits.
#define SET_BITS(variable, bits) ((variable) |= (bits))


// Return the bit number of the least significant bit.
// This can be used for bitshifting.
// Also returns 0 if the bitmask is zero!
#define RIGHTMOST_BIT_NUMBER(variable) ((variable) == 0 ? 0 : __builtin_ffs(variable) - 1)
// This is GCC specific!
// The compiler's return value is 1-indexed, so subtract 1.
// Manually return 0 if the bitmask is 0.

#endif
