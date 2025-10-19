#include "extern.h"

#define PTR_DIFF(end, start) (((void *)end) - ((void *)start))
#define WPTR_INC(wptr, val) \
	++wptr;                 \
	*wptr = 1 + (val << 7)


uint8_t*
comp_rle(uint8_t *bytes, uint32_t size, uint32_t *new)
{
	if (size < 1) {
		/* Size is equal to 0. */
		return NULL;
	}

	/* 
	 * Allocate our return buffer, this will store the compressed data.
	 * In this case we alloc the worst case size.
	 */
	uint8_t *ret = (uint8_t *)malloc(size * 8);
	/* Save the memory location of the start of the return value, this is as the wptr will incriment the buffer. */
	uint8_t *static_ret = ret;
	/* Stores the next location to write to. */
	uint8_t *wptr = ret;
	*wptr = (*bytes & 1u) << 7;

	uint32_t i;
	for (i = 0; i < size; ++i) {
		uint16_t mask = 0x1;
		do {
			/* Check if the current bit is equal to the compression bit in use. */
			register uint8_t curr_bit = (bytes[i] & mask) != 0;
			if (curr_bit != (*wptr) >> 7) {
				WPTR_INC(wptr, curr_bit);
			} else {
				/* This is when the max compressed count has been reached for the data. */
				if ((*wptr << 1) == 254) {
					WPTR_INC(wptr, curr_bit);
				} else {
					++(*wptr);
				}
			}
			mask <<= 1u;
		} while (mask < 129);
	}
	++wptr;

	*new = PTR_DIFF(wptr, static_ret);
	ret = static_ret;
	return ret;
}

