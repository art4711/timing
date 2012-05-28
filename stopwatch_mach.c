#include <inttypes.h>
#include <time.h>
#include <mach/mach_time.h>
#include <libkern/OSAtomic.h>
#include <sys/time.h>

#include "stopwatch.h"

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

