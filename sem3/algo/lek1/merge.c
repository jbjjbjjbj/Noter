#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define DO_PRINT 0

void printArr(int *arr, size_t len) {
	printf("{");
	for(int i = 0; i < len; i++) {
		printf(" %d%s", arr[i], i+1 == len ? " " : ",");
	}
	printf("}\n");
}

int *genArr(size_t len, int div) {
	/* Make array */
	int *arr = (int *) malloc(len * sizeof(int));

	if( arr == NULL) {
		return NULL;
	}

	/* Fill it with random */
	while( len-- ) {
		arr[len] = div - (rand() % (div*2));
	}

	return arr;

}

int mergeSort(int *arr, size_t len) {
	/* Check if len is one(then it's sorted */
	if (len <= 1) {
		return 0;
	}
	/* Calculate array sizes */
	size_t q = len/2;
	size_t rl = len-q;

	/* Make arrays */
	int *left = (int *) malloc(q * sizeof(int));
	if( left == NULL ) {
		return 1;
	}
	int *right = (int *) malloc(rl * sizeof(int));
	if( right == NULL ) {
		return 1;
	}

	/* Copy data */
	memcpy(left, arr, q * sizeof(int));
	memcpy(right, arr + q, rl * sizeof(int));

	/* Sort each */
	mergeSort(left, q);
	mergeSort(right, rl);

	/* Merge them into arr */
	for(int i=0, j=0, k = 0; k < len; k++) {
		if( i < q && ( j == rl || left[i] <= right[j] ) ) {
			arr[k] = left[ i++ ];
		} else {
			arr[k] = right[ j++ ];
		}
	}

	/* Free the pointers */
	free(left);
	free(right);

	return 0;
}

void test(size_t len) {

	int *a = genArr(len, len);

#if DO_PRINT == 1
	printArr(a, len);
	printf("\n\n");
#endif

	clock_t begin = clock();
	mergeSort(a, len);
	clock_t end = clock();

#if DO_PRINT == 1
	printArr(a, len);
#endif

	clock_t diff = end - begin;
	printf("Sorting %d long array took %d : %f s\n", len, diff, (double)diff/CLOCKS_PER_SEC);

	free(a);
}

void bench() {

	size_t len = SIZE_MAX;

	srand((unsigned) time(NULL));
	for (int i = 1; i < len; i *= 2) {
		test(i);
	}
}

int main(void) {

	bench();

	return 0;
}
