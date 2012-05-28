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

#define STATE_TIMER_STOPWATCH(st, state) (&(st)->st_sw[state + 1])

#endif
