#define LEDPIN 13

int task1(void) {
    static bool state = 0;

    digitalWrite(LEDPIN, state);
    state = !state;
    return 0;
}

int task2(void) {
    Serial.print("l");
    return 0;
}
int task3(void) {
    Serial.print("h");
    return 0;
}

int runevery(int (*f)(), unsigned long *last, unsigned long period) {
    unsigned long now = millis();
    if (*last + period > now) {
        return -1;
    }

    *last = now;
    return (*f)();
}


#define TASKS 3
unsigned long lasts[TASKS];

void setup() {
    Serial.begin(115200);
    pinMode(LEDPIN, OUTPUT);
    for (int i = 0; i < TASKS; i++) {
        lasts[i] = 0;
    }
}

void loop() {
    unsigned i = 0;
    runevery(task1, &lasts[i++], 1000);
    runevery(task2, &lasts[i++], 100);
    runevery(task3, &lasts[i++], 10);
}
