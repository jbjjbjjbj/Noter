#include <krnl.h>
#define STACK 100
#define BUTTONPIN 2
#define LEDPIN 13

char stk1[STACK];
struct k_t *tsk1;
struct k_msg_t *pmsg;
char msgbuff[10];

ISR(INT0_vect) {
    static unsigned long last = 0;

    unsigned long now = millis();
    if (now - last < 100) {
        return;
    }
    last = now;

    static char state = 0;
    state = !state;

    ki_send(pmsg, (void *)&state);

}

void f1() {
    while(true) {
        char state;
        int lost;
        if (k_receive(pmsg, &state, 0, &lost) < 0) {
            continue;
        }

        //k_eat_msec_time(1000);

        Serial.print("Lost: "); Serial.println(lost);

        digitalWrite(LEDPIN, state);
    }
}

void setup()
{
    pinMode(LEDPIN, OUTPUT);

	pinMode(BUTTONPIN, INPUT_PULLUP);
	// Enable interrupt 0
	EIMSK |= 1 << INT0;
	// Eable on rising edge
	EICRA |= (1 << ISC01);

    Serial.begin(115200);
    Serial.println("Starting");

    k_init(1, 0, 1);

    pmsg = k_crt_send_Q(10, 1, msgbuff);
    tsk1 = k_crt_task(f1, 10, stk1, STACK);

    k_start(1);
}

void loop()
{

}
