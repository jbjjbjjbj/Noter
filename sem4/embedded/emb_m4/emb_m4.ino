
#include <krnl.h>
#define STACK 100

char stk1[STACK];
char stk2[STACK];
struct k_t *tsk1, *tsk2;

void f1() {
	for(;;) {
		Serial.println("Haha");
	}
}
void f2() {
	bool state = false;
	for(;;) {
		digitalWrite(13, state);
		state = !state;
		k_sleep(1000);
	}
}

void setup()
{
	pinMode(13, OUTPUT);
	Serial.begin(115200);
	Serial.println("Starting");

	k_init(2, 0, 0);

	tsk1 = k_crt_task(f1, 10, stk1, STACK);
	tsk2 = k_crt_task(f2, 10, stk2, STACK);

	k_start(1);
}

void loop()
{
	
}
