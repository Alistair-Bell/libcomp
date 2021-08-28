#ifndef COMP_EXTERN_H
#define COMP_EXTERN_H

/*
 * Small and simple compression library for embedding within projects.
 * Will eventually host range of algorithms for compressing files.
 * Return values are the respective result from encoding or decoding.
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/* Include should be removed in final releases, only used for debugging. */
#include <stdio.h>

uint8_t *comp_rle(uint8_t *, uint32_t);
uint8_t *decomp_rle(uint8_t *, uint32_t);

#endif
