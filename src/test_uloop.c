#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uloop.h"

#define delay_ms 500

typedef enum TIMER_T {
	SET_TIMEOUT,
	SET_INTERVAL
} TIMER_T;

static bool ivalstop=false;

void stop_setInternal(struct uloop_timeout *t)
{
	ivalstop=true;
}

void setTimeout(struct uloop_timeout *t)
{
	// do some stuff here
	fprintf(stderr, "setTimeout!\n");
	uloop_timeout_cancel(t);
}

void setInterval(struct uloop_timeout *t)
{
	if (ivalstop) {
		uloop_timeout_cancel(t);
	} else {
		// do some stuff here
		fprintf(stderr, "setInternal!\n");
		uloop_timeout_set(t, delay_ms);
	}
}

static void initialize_timer(struct uloop_timeout *t, TIMER_T timer_t)
{
	t = (struct uloop_timeout *) malloc (sizeof(struct uloop_timeout));
	memset(t, 0, sizeof(*t));
	t->cb = (timer_t == SET_INTERVAL) ? setInterval : setTimeout;
	uloop_timeout_set(t, delay_ms);
}

int main(int argc, char **argv)
{
	// uloop initialize
	uloop_init();

	// setTimeout
	struct uloop_timeout *timeout;
	initialize_timer(timeout, SET_TIMEOUT);
	
	// setInternal
	struct uloop_timeout *interval;
	initialize_timer(interval, SET_INTERVAL);
	
	// loop start
	uloop_run();
	uloop_done();

	return 0;
}