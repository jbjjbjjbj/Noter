

void setup() {
	Serial.begin(115200);

	Serial.println("Starting the stuff");
	
}

#define ST_PRE 0
#define ST_LEN 1
#define ST_DAT 2
#define ST_CHK_1 3
#define ST_CHK_2 4

#define P_START 0x02
#define P_STOP 0x03
#define P_ESCAPE 0x10

#define ESCAPE(c) P_ESCAPE, (uint8_t)c - P_ESCAPE

struct l2state{
	// See ST_* defines
	int state;
	// Keeps track of data array.
	size_t data_index;
	// Whether to interpret next byte as raw.
	bool doesc;
	// Placeholder for check digits
	uint8_t chk[2];
	// Length of data read in layer 2 header
	size_t len;
};

// Simple test function. Should be replaced with serial.read etc.
uint8_t readnext() {
	static size_t index = 0;
	uint8_t msg[] = {0, 0, 12, 0x12, 123, 40, 120, 0x02, 13, 1, 2, 2, 0, 88, 50, 1, 90, 5, 0, 0, 88, 2, 74, 216, 0x03, 
		0, 0, 0, 0x02, 25, 'A', 0x01, 0, 0, 0x88, ESCAPE(0x10), 3, 23, 0x44, 0, 0, 0xFF, 0xFF, 11, 0xAB, 0, 0, 0xFE, 0xFF, ESCAPE(0x03), 0x40, 0, 0, 0xFF, 0xFF, 50, 125, 0x03, 0, 0, 0, 0};

	// If we reached the end, stop
	if( index > sizeof(msg) / sizeof(uint8_t) ) {
		for(;;);
	}
	return msg[index++ ];
}

// Updates checksum vars in s with input
// The flecker algorithm overflows at 254 not 255
void checksum(struct l2state *s, uint8_t input) {
	s->chk[0] = (s->chk[0] + input) % 255;
	s->chk[1] = (s->chk[1] + s->chk[0]) % 255;
}

void l2reset(struct l2state *s) {
	s->state = ST_PRE;
	memset(s->chk, 0, sizeof(s->chk));
	s->data_index = 0;
}

// Decodes a single character, returning a value > 0 when finished.
// Remember to zero out s
size_t layer2decode(struct l2state *s, uint8_t *data, uint8_t input) {
	/* Commented out because we never check for P_STOP
	// Whether to take input as raw with no special meaning.
	bool escaped = false;
	*/

	// Handle escape
	if( s->state && input == P_ESCAPE ) {
		s->doesc = true;
		return 0;
	}
	if( s->doesc ) {
		input += P_ESCAPE;
		s->doesc = false;
		//escaped = true;
	}

	switch(s->state) {
		case ST_PRE:
			Serial.print("p");
			// Wait for start. 
			// Escaped will not be checked because it will always be false here.
			if(input == P_START) {
				// We are go
				s->state = ST_LEN;
			}
			break;
		case ST_LEN:
			Serial.print("l");
			// Read a single len, and switch state
			s->len = input;
			s->state = ST_DAT;
			break;
		case ST_DAT:
			Serial.print("d");
			// Save input as data byte
			data[s->data_index++] = input;		
			
			// Update checksum
			checksum(s, input);
			
			// Check if we are done
			if(s->data_index >= s->len) {
				s->state = ST_CHK_1;
			}
			break;
		case ST_CHK_1:
			Serial.print("c1");
			// Check with the one calculated through ST_DAT
			if( s->chk[0] != input ) {
				Serial.print("Wrong chk1, expected: "); Serial.println(s->chk[0]);
				l2reset(s);
				break;
			}

			s->state = ST_CHK_2;
			break;
		case ST_CHK_2:
			Serial.print("c2");
			if( s->chk[1] != input ) {
				Serial.print("Wrong chk2, expected: "); Serial.println(s->chk[1]);
				l2reset(s);
				// TODO should return error
				break;
			}

			l2reset(s);
			return s->len;
	}

	return 0;
}

struct l3master {
	uint8_t rssi;
	uint32_t txid : 24;
	uint16_t txidtime;
};

struct l3pkg {
	uint8_t type;
	// Arduino is littleendian( LSByte first ).
	uint32_t recvid : 24;
	// Transducerlevel
	uint8_t trslevel;
	uint8_t quiettime;
	uint8_t nummasters;
	struct l3master masters[0];
};

void printl3pkg(struct l3pkg *l3) {
	Serial.print("Type            :"); Serial.println(l3->type);
	Serial.print("Recvid          :"); Serial.println(l3->recvid);
	Serial.print("Transducerlevel :"); Serial.println(l3->trslevel);
	Serial.print("Quiettime       :"); Serial.println(l3->quiettime);
	Serial.print("Masters         :"); Serial.println(l3->nummasters);

	// Loop the masters
	for(int i = 0; i < l3->nummasters; i++) {
		Serial.print("\nMASTER: "); Serial.println(i);
		Serial.print("    rssi        :"); Serial.println(l3->masters[i].rssi);
		Serial.print("    txid        :"); Serial.println(l3->masters[i].txid);
		Serial.print("    ixidtime    :"); Serial.println(l3->masters[i].txidtime);
	}
}

void loop() {
	struct l2state s;
	// Zero it out
	l2reset(&s);

	uint8_t data[256];

	while(1) {
		uint8_t i = readnext();

		if( layer2decode(&s, data, i) > 0) {
			// Finished package decode
			Serial.println("DONE");

			// Cast to the pkg type
			Serial.println("DONE");
			struct l3pkg *l3 = (struct l3pkg *)data;
			printl3pkg(l3);

		}

	}
}
