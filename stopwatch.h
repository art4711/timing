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

#ifndef STOPWATCH_H
#define STOPWATCH_H

/* Exposed only because it's needed. */
#include <inttypes.h>
struct stopwatch {
	uint64_t t;
};

void stopwatch_reset(struct stopwatch *);
void stopwatch_start(struct stopwatch *);
void stopwatch_stop(struct stopwatch *);
void stopwatch_handover(struct stopwatch *, struct stopwatch *);

struct timeval;
struct timespec;
void stopwatch_to_ts(struct stopwatch *, struct timespec *);
void stopwatch_to_tv(struct stopwatch *, struct timeval *);
int stopwatch_to_s(struct stopwatch *);
double stopwatch_to_ns(struct stopwatch *);

#endif
