/*
 * Copyright (c) 2012 Artur Grabowski <art@blahonga.org>
 * Copyright (c) 2012 Thordur Bjornsson <thib@secnorth.net>
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
#include <sys/time.h>

#include <inttypes.h>
#include <string.h>
#include <time.h>

#include "stopwatch.h"

/*
 * Implementation of the stopwatch API for Linux.
 */

void
stopwatch_reset(struct stopwatch *sw)
{
	sw->t = 0;
}

void
stopwatch_start(struct stopwatch *sw)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	sw->t -= (ts.tv_nsec + (1000000000 * ts.tv_sec));
}

void
stopwatch_stop(struct stopwatch *sw)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	sw->t += (ts.tv_nsec + (1000000000 * ts.tv_sec));
}

void
stopwatch_handover(struct stopwatch *from, struct stopwatch *to)
{
	struct timespec	ts;
	uint64_t	t;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	t = (ts.tv_nsec + (1000000000 * ts.tv_sec));

	from->t += t;
	to->t -= t;
}

void
stopwatch_snapshot(struct stopwatch *from, struct stopwatch *to)
{
	struct timespec ts;
	uint64_t	t;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	t = (ts.tv_nsec + (1000000000 * ts.tv_sec));

	to->t = from->t + t;
}

/*
 * XXX - The math in here is most likely incorrect wrt. overflows.
 *       Deal with it when awake.
 */

void
stopwatch_to_ts(struct stopwatch *sw, struct timespec *ts)
{
	ts->tv_sec = sw->t / 1000000000;
	ts->tv_nsec = sw->t % 1000000000;
}

void
stopwatch_to_tv(struct stopwatch *sw, struct timeval *tv)
{
	tv->tv_sec = sw->t / 1000000000;
	tv->tv_usec = (sw->t % 1000000000) / 1000;
}

int
stopwatch_to_s(struct stopwatch *sw)
{
	return sw->t / 1000000000;
}

double
stopwatch_to_ns(struct stopwatch *sw)
{
	return (double)sw->t;
}
