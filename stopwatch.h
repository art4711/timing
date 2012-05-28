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
