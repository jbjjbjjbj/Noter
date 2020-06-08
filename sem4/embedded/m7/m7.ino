#include <krnl.h>
#define STACK 200

char stk1[STACK];
char stk2[STACK];
struct k_t *tsk1, *tsk2, *sem1, *sem2;

#define DELAY 100000
void f1() {
    k_set_sem_timer(sem1, 50);
	for(;;) {
        k_wait(sem1, 0);
        PORTD &= ~(1 << 5);
        PORTD |= (1 << 4);
        k_eat_msec_time(20);
        PORTD &= ~(1 << 4);
	}
}

void f2() {
    k_set_sem_timer(sem2, 80);
	for(;;) {
        k_wait(sem2, 0);
        PORTD &= ~(1 << 5);
        PORTD |= (1 << 3);
        k_eat_msec_time(20);
        PORTD &= ~(1 << 3);
	}
}

void setup() {
    pinMode(13, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    Serial.begin(115200);
    Serial.println("Starting");

    k_init(2, 2, 0);

    sem1 = k_crt_sem(0, 1);
    sem2 = k_crt_sem(0, 1);

    tsk1 = k_crt_task(f1, 10, stk1, STACK);
    tsk2 = k_crt_task(f2, 10, stk2, STACK);

    k_start(1); 
}

void loop() {

}
