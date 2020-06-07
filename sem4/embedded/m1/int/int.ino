#define LEDPIN 13
#define BUTTONPIN 2

#define DEBOUNCE 1

ISR(INT0_vect) {
    static unsigned long last = 0;

    unsigned long now = millis();
    if (now - last < 100) {
        return;
    }
    last = now;

	static unsigned char state = 0;

	// Toggle LEDPIN
	digitalWrite(LEDPIN, state % 2 == 0);
	state++;
    Serial.print("Hej "); Serial.println(state);

}

void setup() {

	// We need to talk
	Serial.begin(9600);

	// Setup pinmodes
	pinMode(LEDPIN, OUTPUT);
	pinMode(BUTTONPIN, INPUT_PULLUP);

	// Attach a interrupt on the button
	//attachInterrupt(digitalPinToInterrupt(BUTTONPIN), testy, RISING);
	
	// Enable interrupt 0
	EIMSK |= 1 << INT0;
	// Eable on rising edge
	EICRA |= (1 << ISC01) | (1 << ISC00);

}

void loop() {
	static int i = 0;

	//Serial.print("Cool stuff happening now ");
	//Serial.println(i++);

}
