#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stopwatch.h"

int
main(int argc, char **argv)
{
	struct stopwatch sw;

	stopwatch_reset(&sw);

	stopwatch_start(&sw);
	usleep(1000000);
	stopwatch_stop(&sw);

	printf("%f (%f)\n", stopwatch_to_ns(&sw), fabs(stopwatch_to_ns(&sw) - 1000000000.0) / 1000000000.0);

	return 0;
}
