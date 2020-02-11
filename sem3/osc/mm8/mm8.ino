// Spg kernel
#include <krnl.h>

#define PRIO 10
#define STACK 100

char stackFast[STACK];
struct k_t *semFast, *fastTask;

void fast() {
	/* Gotta go fast(10 Hz) */
	k_set_sem_timer(semFast, 1000);
	for(;;) {
		k_wait(semFast, 0);
		k_eat_ticks(90);
	}
}

void setup() {
	pinMode(13, OUTPUT);

	PORTB |= 0x20;
	delay(1000);
	PORTB &= 0xDF;
	delay(200);

	k_init(1, 1, 0);
	
	fastTask = k_crt_task(fast, PRIO, stackFast, STACK);
	semFast = k_crt_sem(0, 2);

	k_start(1);
	PORTB |= 0x20;
}

void loop() {}

extern "C" {

	void k_breakout() {
		if( pRun->nr == 0 ) {
			PORTB |= 0x20;
		} else {
			PORTB &= 0xDF;
		}
	}
}
