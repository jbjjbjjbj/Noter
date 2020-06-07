#include "myfloat_red.h"

// Number of numbers
#define NN 100
#define PRINT_PRECISION 10

#define NEXT_OPG(c) Serial.print("\nOpgave "); Serial.println(c++);
#define AND_OPG(c) Serial.print("and "); Serial.println(c++);

unsigned int opg_count = 1;

void printmydoubarr(myfloat_type *arr, size_t len) {
	Serial.print("[ ");
	for(size_t i = 0; i < len; i++) {
		Serial.print(myfloat2double( &arr[i] ), PRINT_PRECISION);
		Serial.print(" ");
	}
	Serial.println("]");
}

void printarr(double *arr, size_t len) {
	Serial.print("[ ");
	for(size_t i = 0; i < len; i++) {
		Serial.print(arr[i], PRINT_PRECISION);
		Serial.print(" ");
	}
	Serial.println("]");
}

unsigned long factorial(unsigned int n) {
	unsigned long res = 1;
	for(unsigned int i = 2; i <= n; i++) {
		res *= i;
	}

	return res;
}

double sineTayler(double x, unsigned int n) {
	double sum = 0;

	for(unsigned int i = 0; i <= n; i++) {
		sum += ((double)pow(-1, i) / (double)factorial(2 * i + 1)) * (double)pow(x, 2 * i + 1);
	}


	return sum;
}

#define TAU 1.57079632679
// After some trial and error the best TAYLORN was 2
#define TAYLORN 2
double sine(double x) {

	// Works by finding value in specific -pi/2 to pi/2 period.
	int period = x / TAU;

	// Remember to multiply with sign
	int sign = x < 0 ? -1 : 1;

	// One cycle of sin takes 4 periods.
	// If 0 just return the sine approx x
	// If 1 do negative sine approx on x - TAU
	// If 2 do negative sine approx x
	// If 3 do sine approx on period x - TAU
	x = abs(x) - abs(TAU*period);

	double res = 12;
	
    Serial.print("Period "); Serial.println(abs(period % 4));
	switch( abs(period % 4) ) {
		case 0:
			res = sineTayler(x, TAYLORN);
			break;
		case 1:
			res = -sineTayler(x - TAU, TAYLORN);
			break;
		case 2:
			res = -sineTayler(x, TAYLORN);
			break;
		case 3:
			res = sineTayler(x - TAU, TAYLORN);
			break;
	}

	// Should never return because all cases are handled
	return res * sign;

}

void mean_rel_error(double *da, myfloat_type *mda, size_t len, double *sign) {
	// Calculate and print the relative error using the formula
	//  X - x
	//  -----   Where x is the calculated value and X is the real value( As real as double gets )
	//    X
	double errorsum = 0;
	Serial.print("Rel Err : [ ");
	for(size_t i = 0; i < len; i++) {
		//Serial.println(errorsum, PRINT_PRECISION);
		// Make space for sign
		if( sign[i] < 0 ) {
			Serial.print(" ");
		}
		// Handle devide by 0
		double error = da[i] ? abs(da[i] - myfloat2double(&mda[i])) / abs(da[i]) : 0;
		Serial.print(error, PRINT_PRECISION);
		Serial.print(" ");

		// Save sum for mean
		errorsum += error;
	}
	Serial.println("]");

	// Calculate mean
	double mean = errorsum / len;
	Serial.print("Mean Err: "); Serial.println(mean, PRINT_PRECISION);
}

void setup() {
	Serial.begin(115200);

	NEXT_OPG(opg_count);
	// OPG1. Create some doubles 
	double da[NN];
	for(int i = 0; i < NN; i++) {
		da[i] = ((double)random(-5000, 5000)) / 1000.0;
	}
	Serial.print("Original: "); printarr(da, NN);

	NEXT_OPG(opg_count);
	// OPG2. Convert to mda
	myfloat_type mda[NN];
	for(int i = 0; i < NN; i++) {
		doub2mydouble(da[i], &mda[i]);
	}

	Serial.print("Mydoub  : "); printmydoubarr(mda, NN);

	NEXT_OPG(opg_count);
	// OPG3. Calculate the mean relative error
	mean_rel_error(da, mda, NN, da);

	{
		NEXT_OPG(opg_count);
		// OPG4. Compute some stuff
		double da2[NN];
		for(int i = 0; i < NN; i++) {
			da2[i] = da[i] * da[i];
		}
		Serial.print("Orig pow: "); printarr(da2, NN);

		NEXT_OPG(opg_count);
		// OPG5.
		myfloat_type mda2[NN];
		for(int i = 0; i < NN; i++) {
			// This thing sometimes does weird stuff -4.06*(-4.06) -> -16.00
			mult_float(&mda[i], &mda[i], &mda2[i]);
		}
		Serial.print("Mda  pow: "); printmydoubarr(mda2, NN);

		NEXT_OPG(opg_count);
		// OPG6. Doing the mean error thing
		mean_rel_error(da2, mda2, NN, da);
	}

	{
		// OPG7. Measure execution time
		NEXT_OPG(opg_count);
		double a = da[1];
		unsigned long begin = micros();
		for(int i = 1; i < NN; i++) {
			a *= da[i];
		}

		unsigned long time1 = micros() - begin;
		Serial.print("Exe time: "); Serial.println(time1);
		Serial.print("a       : "); Serial.println(a);

		NEXT_OPG(opg_count);
		// Convert to myfloat
		myfloat_type f1;
		doub2mydouble(a, &f1);

		Serial.print("f1      : "); Serial.println(myfloat2double(&f1));

		NEXT_OPG(opg_count);
		// OPG8-9.
		begin = micros();
		for(int i = 0; i < NN; i++) {
			// Multiply
			myfloat_type f;
			mult_float(&f1, &mda[i], &f);

			// Copy back
			memcpy(&f1, &f, sizeof(myfloat_type));
		}

		unsigned long time2 = micros() - begin;
		Serial.print("Exe time: "); Serial.println(time2);
		Serial.print("f1      : "); Serial.println(myfloat2double(&f1));
		Serial.println("Overflow");

		NEXT_OPG(opg_count);
		// OPG10. Difference relative to biggest result

		unsigned long absdiff = abs( time1 - time2 );
		Serial.print("Abs diff: "); Serial.println(absdiff);
		double reldiff = (double)absdiff / max(abs(time1), abs(time2));
		Serial.print("Rel diff: "); Serial.println(reldiff);
	}

	NEXT_OPG(opg_count);
	// OPG11. Impl sine
	// Hardest value should be TAU as it's the furthest from center.
#define STEPS 100
    double start = -100;
    double end = 100;
    double step = (end - start) / (STEPS-1);
    unsigned long owntotaltime = 0;
    unsigned long ardtotaltime = 0;
    double totalerror = 0;
    for (int i = 0; i < STEPS; i++) {
        Serial.print("\n\nInput: "); Serial.println(start, PRINT_PRECISION);

        unsigned long begin = micros();
        double res = sine(start);
        unsigned long time1 = micros() - begin;
        Serial.print("own sin : "); Serial.println(res, PRINT_PRECISION);

        begin = micros();
        double correct = sin(start);
        unsigned long time2 = micros() - begin;
        Serial.print("ard sin : "); Serial.println(correct, PRINT_PRECISION);

        double error = correct ? abs(correct - res) / abs(correct) : 0;
        Serial.print("rel err : "); Serial.println(error, PRINT_PRECISION);

        Serial.print("own time: "); Serial.println(time1);
        Serial.print("ard time: "); Serial.println(time2);

        owntotaltime += time1;
        ardtotaltime += time2;
        totalerror += error;

        start += step;
    }
    Serial.println("\n\nTOTAL STATS");
    Serial.print("rel err : "); Serial.println(totalerror / STEPS, PRINT_PRECISION);
    Serial.print("own time: "); Serial.println(owntotaltime / STEPS);
    Serial.print("ard time: "); Serial.println(ardtotaltime / STEPS);

}

void loop() {

}
