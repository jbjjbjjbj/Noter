#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <complex.h>
#include <math.h>

// Needed for option parsing
#include <unistd.h>
#include <string.h>

#define MAX_FILE_SIZE 10000

typedef uint16_t index_t;
typedef complex double val_t;

// Make a better version of this
index_t reverse_bits(index_t i, unsigned fft_size)
{
    unsigned n = fft_size;
    index_t reverse = 0;

    while (n--) {
        reverse <<= 1;
        reverse |= i & 1;
        i >>= 1;
    }

    return reverse;
}

val_t twiddle(index_t N, int k)
{
    val_t in = (2 * M_PI)/(double)N;
    val_t res = cexp(-in * k * I);
    return res;
}

void butterfly_single(val_t *buf, index_t a, index_t b, val_t twid)
{
    val_t common = twid * buf[b];

    buf[b] = buf[a] - common;
    buf[a] += common;
}

void butterfly(val_t *buf, unsigned depth, index_t n, index_t N)
{
    if (n == 2) {
        butterfly_single(buf, 0, 1, twiddle(N, 0));
        return;
    }

    n = n/2;
    index_t step = pow(2, depth);

    for (index_t i = 0; i < n; i++) {
        butterfly_single(buf, i, i + n, twiddle(N, i * step));
    }
}

void fft_inplace_recur(val_t *buf, unsigned depth, index_t n, index_t N)
{
    if (n > 2) {
        index_t split = n/2;
        fft_inplace_recur(buf, depth+1, split, N);
        fft_inplace_recur(buf+split, depth+1, split, N);
    }

    butterfly(buf, depth, n, N);
}

val_t *fft(val_t *buf, size_t input_size, size_t N)
{
    // Check if power of two
    if ((N & (N - 1)) != 0) {
        fprintf(stderr, "FFT size %lu must be power of two\n", N);
        return NULL;
    }

    val_t *tmpbuf = (val_t *) malloc(sizeof(val_t) * N);

    // Reverse bits
    int least = input_size < N ? input_size : N;
    for (int i = 0; i < least; i++) {
        index_t reverse = reverse_bits(i, log2(N));
        tmpbuf[i] = buf[reverse];
    }

    // Padding
    for (int i = 0; i < (int)N - least; i++) {
        tmpbuf[i + least ] = 0;
    }

    fft_inplace_recur(tmpbuf, 0, N, N);
    return tmpbuf;
}

void printhelp(char *prog) {
    printf("Usage: %s [options]\n", prog);
    puts("Options:");
    puts("  -h          This help screen");
    puts("  -o <FILE>   Write output to file");
    puts("  -i <FILE>   Read from file");
    puts("  -f <SIZE>   FFT size, must be power of two");
    puts("");
    printf("FILE should not have more than %d lines, with line seperated values.\n", MAX_FILE_SIZE);
    puts("FILE will default to stdin/stdout");
}

int main(int argc, char **argv)
{
    int opt;
    int optfft = -1;
    char *input = NULL;
    char *output = NULL;

    while ((opt = getopt(argc, argv, "hi:o:f:")) != -1) {
        switch(opt) {
            case 'o':
                output = strdup(optarg);
                break;
            case 'i':
                input = strdup(optarg);
                break;
            case 'f':
                optfft = strtol(optarg, NULL, 10);
                break;
            case 'h':
            default:
                printhelp(argv[0]);
                return 0;
        }
    }

    if (optfft == -1) {
        fprintf(stderr, "FFT not specified\n");
        printhelp(argv[0]);
        return 1;
    }

    // Allocate storage
    val_t *buf = (val_t *) malloc(sizeof(val_t) * MAX_FILE_SIZE);
    if (buf == NULL) {
        printf("Could not allocate mega array\n");
        return 1;
    }

    FILE *f = stdin;
    if (input != NULL) {
        f = fopen(input, "r");
        if (f == NULL) {
            printf("Could not open file %s\n", input);
            return 1;
        }
    }

    double val;
    int length;
    for (length = 0; fscanf(f, "%lf\n", &val) != EOF; length++) {
        buf[length] = (val_t) val;
        //printf("Val: %lf + j%lf\n", creal(buf[ii]), cimag(buf[ii]));
    }

    val_t *res = fft(buf, length, optfft);
    if (res == NULL) {
        fprintf(stderr, "Error calculating fft\n");
        return 1;
    }

    f = stdout;
    if (output != NULL) {
        f = fopen(output, "w");
        if (f == NULL) {
            printf("Could not open file %s\n", input);
            return 1;
        }
    }

    for (int ii = 0; ii < optfft; ii++) {
        fprintf(f, "%lf%+lfj\n", creal(res[ii]), cimag(res[ii]));
    }
}
