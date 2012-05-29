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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "state_timer.h"

int
main(int argc, char **argv)
{
	int i;

	STATE_TIMER(5) timers;

	STATE_TIMER_RESET(&timers, 5);

	for (i = 0; i < 20; i++) {
		STATE_TIMER_ENTER(&timers, i % 5);
		usleep(200000);
	}

	for (i = 0; i < 5; i++) {
		struct stopwatch sw;
		double ns;

		STATE_TIMER_STOPWATCH(&timers, i, &sw);
		ns = stopwatch_to_ns(&sw);

		printf("%d: %f\n", i, ns);
	}

	return 0;
}

