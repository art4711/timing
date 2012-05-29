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

#ifndef STATE_TIMER_H
#define STATE_TIMER_H
#include "stopwatch.h"

#define STATE_TIMER(nstates) struct { \
	struct stopwatch st_sw[nstates + 1]; \
	int st_state; \
}

#define STATE_TIMER_RESET(st, ns) do { \
	int _i; \
	for (_i = 0; _i < ns + 1; _i++) \
		stopwatch_reset(&(st)->st_sw[_i]); \
	stopwatch_start(&(st)->st_sw[0]); \
	(st)->st_state = 0; \
} while (0)

#define STATE_TIMER_ENTER(st, state) do { \
	int _state = state; \
	stopwatch_handover(&(st)->st_sw[(st)->st_state], &(st)->st_sw[_state + 1]); \
	(st)->st_state = _state + 1; \
} while (0)

#define STATE_TIMER_STOP(st) STATE_TIMER_ENTER((st), -1)

#define STATE_TIMER_STOPWATCH(st, state, res) do {\
	int _state = (state + 1); \
	if (_state == (st)->st_state) \
		stopwatch_snapshot(&(st)->st_sw[_state], res); \
	else \
		*(res) = ((st)->st_sw[_state]); \
} while (0)

#endif
