#ifndef __BitManip_H
#define __BitManip_H

// Set a single or several bits given by a bitmask.
// This macro will not clear bits.
#define SET_BITS(variable, bits) ((variable) |= (bits))

#endif
