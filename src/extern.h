/*
 * Copyright (c) 2021 Alistair Bell <alistair@alistairbell.xyz>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

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

uint8_t *comp_rle(uint8_t *, uint32_t, uint32_t *);
uint8_t *decomp_rle(uint8_t *, uint32_t, uint32_t *);

#endif
