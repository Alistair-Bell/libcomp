#include "extern.h"

#define WPTR_INC(wptr, val) *wptr = val; ++wptr

uint8_t*
comp_rle(uint8_t *bytes, uint32_t size)
{
	/* Allocate a buffer size equal to the worst case compression. */
	uint8_t *ret = malloc(size * 8);
	/* Set the byte ptr to the start of the byte array. */
	uint8_t *bptr = &(*bytes);
	/* Stores the memory adress of the next write location to the return buffer. */
	uint8_t *wptr = &(*ret);
	/* Set the most significent bit to the current value being compressed. */
	register uint8_t acc = *bptr << 7;

	for (; bptr < bytes + size; ++bptr) {
		uint8_t i;
		for (i = 0; i < 8; ++i) {
			/* Test the current compression bit is equal to the bit being analysed. */
			if ((*bptr >> i & 1 ) == (acc >> 7)) {
				/* Validate that there is no carry to the current value bit. */
				if (1) {
					++acc;
				} else {
					/* Write the byte to the write ptr. */
					WPTR_INC(wptr, acc);
					/* Use a bitmask and subtract the lower 7 bits. */
					acc -= (acc & 127);	
				}
			} else {
				fprintf(stdout, "acc before switch %d\n", acc);
				/* Write the previous compression byte. */
				WPTR_INC(wptr, acc);
				/* Toggle the target value bit in `acc`. */
				acc ^= 128;
				/* Reset the least significent bits. */
				acc -= (acc & 127);
			}
		}
	}
	return ret;
}

