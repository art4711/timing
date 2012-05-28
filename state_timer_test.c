#include <stdio.h>
#include <stdlib.h>

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

	STATE_TIMER_STOP(&timers);
	for (i = 0; i < 5; i++) {
		double ns = stopwatch_to_ns(STATE_TIMER_STOPWATCH(&timers, i));

		printf("%d: %f\n", i, ns);
	}

	return 0;
}

