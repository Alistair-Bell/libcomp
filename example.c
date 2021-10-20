#include "src/extern.h"

#define ARR_LEN(x) sizeof(x) / sizeof(x[0])

int
main(void)
{
	uint8_t bytes[] = { 
		0xff,
		0xff,
		0xff,
		0xf0,
	};
	uint32_t len, len2;
	uint8_t *res = comp_rle(bytes, ARR_LEN(bytes), &len);
	uint8_t *dec = decomp_rle(res, len, &len2);

	uint32_t i;
	for (i = 0; i < len2; ++i) {
		fprintf(stdout, "%d : %d\n", bytes[i], dec[i]);
	}

	free(res);
	free(dec);
}
