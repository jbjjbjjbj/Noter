#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define STARTSEC 10
#define ENDUSEC 500000
#define SPEED 0.8

struct itimerval timer;

void timer_handler(int signum)
{
    /* Handy structure reference */
    struct timeval *tv = &timer.it_value;
    printf("Hey we hit the alarm\n\a");

    /* Calculate new alarm */
    tv->tv_sec *= SPEED;
    if (tv->tv_sec == 0) {
	/* If tv_usec is 0 set i to 1 sec otherwise half it */
	if (tv->tv_usec == 0) {
	    tv->tv_usec = 999999;
	} else if (tv->tv_usec > ENDUSEC) {
		tv->tv_usec *= SPEED;
	    if (tv->tv_usec < ENDUSEC) {
			tv->tv_usec = ENDUSEC;
	    }
	} else {
	    /* Return letting the timer be set to ENDUSEC */
	    return;
	}
    }

    printf("Set to %d and %d\n", timer.it_value.tv_sec, timer.it_value.tv_usec);
    /* Set alarm */
    int err = setitimer(ITIMER_REAL, &timer, NULL);
    if (err) {
		printf("Hey we got an error guys\n");
		exit(1);
    }
}

int main()
{
    /* Setup handler for timer */
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa)); /* Remeber to set all fields to zero */

    sa.sa_handler = &timer_handler;
    sigaction(SIGALRM, &sa, NULL);

    /* Setup timer values */
    timer.it_value.tv_sec = STARTSEC;
    timer.it_value.tv_usec = 0;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = ENDUSEC;

    /* Start the timer */
    setitimer(ITIMER_REAL, &timer, NULL);

    /* Select signals */
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGTERM);

    /* Wait for termination */
    sigwait(&sigset, NULL);

    return 0;
}
