#include "regs.h"

struct tsk {
	uint8_t stack_h;
	uint8_t stack_l;

	struct tsk *next;
};

struct tsk *cur = NULL;
struct tsk *tasks = NULL;

// Setup a timer running every 10 ms
void timersetup()
{
	noInterrupts();

	TCNT1 = 0;

	// Enable CTC and set prescaler = 1024.
	// This will give a freq of 15625
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);

	// Clear on match
	//TCCR1A = (1 << COM1A1);
	TCCR1A = 0;

	// Setup compare. Must be around 156 to create 10ms
	OCR1A = 156;

	// Enable interrupt on compare
	TIMSK1 |= (1 << OCF1A);

	interrupts();
}

inline struct tsk *get_next() {
	if (cur->next) {
		return cur->next;
	}

	return tasks;
}

void create_tsk(struct tsk *t, void (*f)(void), uint8_t *stack, size_t len) {
	// Move to the end of stack
	uint8_t *s = stack + len - 1;
	
	// Push load address
	*(s--) = (uint16_t)f & 0xFF;
	*(s--) = ((uint16_t)f >> 8) & 0xFF;

	// Push all the stuff. Reg + SREG
	for (int i = 0; i < 32 + 1; i++) {
		*(s--) = 0;
	}

	// Save the stack pointer
	t->stack_l = (uint16_t)s & 0xFF;
	t->stack_h = ((uint16_t)s >> 8) & 0xFF;

	// Put it on the list
	t->next = tasks;
	tasks = t;
}

void run() {
	cur = tasks;

	// Put it back
	SPL = cur->stack_l;
	SPH = cur->stack_h;

	POPREGS();
	__asm__("RETI");
}

void func(void) {
	for(;;) {
		Serial.println(1);
	}
}
void func3(void) {
	for(;;) {
		Serial.println(3);
	}
}
void func4(void) {
	for(;;) {
		Serial.println(4);
	}
}

void func2(void) {
	bool state = false;
	for(;;) {
		digitalWrite(13, state);
		state = !state;
		delay(1000);
	}
}

ISR(TIMER1_COMPA_vect, ISR_NAKED)
{
	PUSHREGS();

	if (!cur) {
		goto exit;
	}

	// Save stack space 
	cur->stack_l = SPL;
	cur->stack_h = SPH;

	// Switch
	cur = get_next();	

	// Put it back
	SPL = cur->stack_l;
	SPH = cur->stack_h;

exit:

	POPREGS();
	__asm__("RETI");
}

void setup()
{
	pinMode(13, OUTPUT);
	Serial.begin(115200);

	Serial.println("Starting stuff");

	struct tsk task1, task2, task4, task3;
	uint8_t stack[100], stack2[100], stack3[100], stack4[100];

	timersetup();

	create_tsk(&task1, func, stack, 100);
	create_tsk(&task2, func2, stack2, 100);
	create_tsk(&task3, func3, stack3, 100);
	create_tsk(&task4, func4, stack4, 100);

	run();

}

void loop()
{
}


