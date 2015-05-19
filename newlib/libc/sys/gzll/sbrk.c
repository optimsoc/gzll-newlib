/* sbrk.c -- allocate space on heap on OpenRISC 1000.
 *
 * Copyright (c) 2014 Authors
 *
 * Contributor Stefan Wallentowitz <stefan.wallentowitz@tum.de>
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 */

#include <stddef.h>
#include <stdint.h>

#include <reent.h>

static uint32_t gzll_heap_end;

void *
_sbrk_r (struct _reent *reent, ptrdiff_t incr)
{
	extern uint32_t	end; /* Set by linker.  */
	uint32_t prev_heap_end;

	if (gzll_heap_end == 0) {
		gzll_heap_end = &end;
	}

	prev_heap_end = gzll_heap_end;
	gzll_heap_end += incr;


	return (void*) prev_heap_end;
}
