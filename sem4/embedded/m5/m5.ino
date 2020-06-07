#include <krnl.h>
#define STACK 200

char stk1[STACK];
char stk2[STACK];
struct k_t *tsk1, *tsk2, *sem;

unsigned long shared1 = 0;
unsigned long shared2 = 0;

#define DELAY 100000
void f1() {
	for(;;) {
        for (int i = 0; i < DELAY/4; i++);
        unsigned long s1 = shared1;

        // Lock
        k_wait(sem, 0);
        unsigned long s2 = shared2;
        // Unlock
        k_signal(sem);

        if (s1 != 0) {
            Serial.print("S1: "); Serial.println(s1);
        }
        if (s2 != 0) {
            Serial.print("S2: "); Serial.println(s2);
        }
	}
}

void f2() {
	for(;;) {
        shared1 += 1;
        for (int i = 0; i < DELAY; i++);
        shared1 -= 1;

        // Lock
        k_wait(sem, 0);
        shared2 += 1;
        for (int i = 0; i < DELAY; i++);
        shared2 -= 1;
        // Unlock
        k_signal(sem);
	}
}

void setup() {
    pinMode(13, OUTPUT);
    Serial.begin(115200);
    Serial.println("Starting");

    k_init(2, 1, 0);

    sem = k_crt_sem(1, 1);

    tsk1 = k_crt_task(f1, 10, stk1, STACK);
    tsk2 = k_crt_task(f2, 10, stk2, STACK);

    k_start(1); 
}

void loop() {

}
