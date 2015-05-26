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
static uint32_t alloc_end;

static inline uint32_t syscall(uint32_t id, uint32_t p0, uint32_t p1)
{
	register uint32_t r11 __asm__("r11") = id;
	register uint32_t r3 __asm__("r3") = p0;
	register uint32_t r4 __asm__("r4") = p1;

	__asm__ __volatile__ ("l.sys 0" : "=r"(r11) : "r"(r11), "r"(r3),
			      "r"(r4) : "memory");

	return r11;
}


void *
_sbrk_r (struct _reent *reent, ptrdiff_t incr)
{
	extern uint32_t	end; /* Set by linker.  */
	uint32_t prev_heap_end;

	if (gzll_heap_end == 0) {
		gzll_heap_end = &end;
		alloc_end = (gzll_heap_end & ~0x1fff) + 0x2000;
	}

	prev_heap_end = gzll_heap_end;
	gzll_heap_end += incr;

	if(gzll_heap_end > alloc_end) {
	    alloc_end = syscall(1, alloc_end, gzll_heap_end - alloc_end);
	}

	return (void*) prev_heap_end;
}
