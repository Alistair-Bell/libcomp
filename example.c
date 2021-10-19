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
	free(res);
}
