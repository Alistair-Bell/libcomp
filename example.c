#include "src/extern.h"

#define ARR_LEN(x) sizeof(x) / sizeof(x[0])

int
main(void)
{
	uint8_t bytes[] = { 
		0xff,
		0xff,
		0xff,
		0xff,
		0xff,
		0xff,
		0x00,
		0xff,
	};
	uint32_t len;
	uint8_t *res = comp_rle(bytes, ARR_LEN(bytes), &len);

	for (uint32_t i = 0; i < len; ++i) {
		uint8_t b = res[i];	
		fprintf(stdout, "byte %d, compression_bit %d, count %d\n", i + 1, (b & 128) >> 7, (b & 127));
	}

	free(res);
}
