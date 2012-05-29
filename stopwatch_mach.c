/*
 * Copyright (c) 2012 Artur Grabowski <art@blahonga.org>
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

#include <inttypes.h>
#include <time.h>
#include <mach/mach_time.h>
#include <libkern/OSAtomic.h>
#include <sys/time.h>

#include "stopwatch.h"

/*
 * Implementation of the stopwatch API for MacOS.
 */

void
stopwatch_reset(struct stopwatch *sw)
{
	sw->t = 0;
}

void
stopwatch_start(struct stopwatch *sw)
{
	sw->t -= mach_absolute_time();
}

void
stopwatch_stop(struct stopwatch *sw)
{
	sw->t += mach_absolute_time();
}

void
stopwatch_handover(struct stopwatch *from, struct stopwatch *to)
{
	uint64_t t = mach_absolute_time();
	from->t += t;
	to->t -= t;
}

void
stopwatch_snapshot(struct stopwatch *from, struct stopwatch *to)
{
	to->t = from->t + mach_absolute_time();
}


static mach_timebase_info_data_t tb;
static void
tb_init(void)
{
	mach_timebase_info_data_t ttb;
	if (tb.denom)
		return;
	mach_timebase_info(&ttb);

	tb.numer = ttb.numer;
	OSMemoryBarrier();
	tb.denom = ttb.denom;
}

/*
 * XXX - The math in here is most likely incorrect wrt. overflows.
 *       Deal with it when awake.
 */
void
stopwatch_to_ts(struct stopwatch *sw, struct timespec *ts)
{
	int64_t ns;
	tb_init();
	ns = sw->t * tb.numer / tb.denom;
	ts->tv_sec = ns / 1000000000;
	ts->tv_nsec = ns % 1000000000;
}

void
stopwatch_to_tv(struct stopwatch *sw, struct timeval *tv)
{
	int64_t ns;
	tb_init();
	ns = sw->t * tb.numer / tb.denom;
	tv->tv_sec = ns / 1000000000;
	tv->tv_usec = (ns % 1000000000) / 1000;
}

int
stopwatch_to_s(struct stopwatch *sw)
{
	int64_t ns;
	tb_init();
	ns = sw->t * tb.numer / tb.denom;
	return ns / 1000000000;
}

double
stopwatch_to_ns(struct stopwatch *sw)
{
	tb_init();
        return ((double)sw->t * (double)tb.numer / (double)tb.denom);
}

