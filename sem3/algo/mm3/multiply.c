#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

uint64_t mult(uint64_t x, uint64_t y, unsigned int bits)
{
	/* Check if they expect more than 64 bits. */
	if ( bits > 64 ) {
		printf("Sorry we cant handle higher than 64 bits\n");
		exit(1);
	} else if (bits <= 1) {
		return x && y;
	}

	unsigned int newBits = bits >> 1;

#if DO_PRINT == 1
	printf("\n\n bits: %u, New bits: %u\n", bits, newBits);
#endif 

	/* Split up into to */
	uint32_t halvMask = ((uint64_t)1 << newBits) - 1;
#if DO_PRINT == 1
	printf("Using mask 0x%08X\n", halvMask);
#endif 
	uint32_t a = (x >> (newBits)) & halvMask;
	uint32_t b = x & halvMask;
	uint32_t c = (y >> (newBits)) & halvMask;
	uint32_t d = y & halvMask;

#if DO_PRINT == 1
	printf("A: 0x%08X, B: 0x%08X, C: 0x%08X, D: 0x%08X\n", a, b, c, d);
#endif 

	return (mult(a, c, newBits) << bits) + ((mult(a, d, newBits) + mult(b, c, newBits)) << newBits) + mult(b, d, newBits);

}


int main(void)
{

	uint32_t a = 0xFFFFFF;
	uint8_t  b = 55;
	uint64_t res;

	clock_t begin = clock();
	res = mult(a, b, 64);
	clock_t end = clock();

	printf("Result: %lld\n", res);

	clock_t diff = end - begin;
	printf("Took %d which is %f s\n", diff, (double)diff/CLOCKS_PER_SEC);
	
	return 0;
}
