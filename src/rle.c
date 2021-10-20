#include "extern.h"

#define PTR_DIFF(end, start) \
	(((void *)end) - ((void *)start))

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

	uint8_t *ret = (uint8_t *)malloc(size * 8);
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

	*new = PTR_DIFF(wptr, ret);
	return ret;
}
uint8_t *
decomp_rle(uint8_t *compressed, uint32_t count, uint32_t *new)
{
	if (count < 1) {
		return NULL;
	}

	uint8_t *ret, *wptr;
	uint16_t write_mask = 0x1;
	uint32_t i, alloc_count = count * 6;

	ret  = (uint8_t *)malloc(alloc_count * sizeof(*ret));
	/* Set the write pointer to the start of the return value, zero the first value. */
	wptr = &(*ret);
	*wptr |= *wptr;

	for (i = 0; i < count; ++i) {
		uint32_t write_count = compressed[i] & 127;
		while (write_count != 0) {
			if (write_mask > 128) {
				write_mask = 1;
				/* Check for reallocation of the out buffer, incriment the write pointer. */
				if (((uint32_t)PTR_DIFF(wptr, ret)) == alloc_count + 1) {
					alloc_count += 15;
					ret = (uint8_t *)realloc((void *)ret, alloc_count * sizeof(*ret));
				}
				++wptr;
			}
			*wptr += write_mask * ((compressed[i] & 128) >> 7);
			write_mask <<= 1u;
			--write_count;
		}
	}
	++wptr;

	*new = PTR_DIFF(wptr, ret);
	return ret;
}

