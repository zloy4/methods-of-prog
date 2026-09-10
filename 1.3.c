#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void fft(double _Complex *a, int n, int invert) {
    if (n <= 1) return;

    double _Complex *even = malloc(n / 2 * sizeof(double _Complex));
    double _Complex *uneven = malloc(n / 2 * sizeof(double _Complex));

    for (int i = 0; i < n / 2; i++) {
        even[i] = a[i * 2];
        uneven[i] = a[i * 2 + 1];
    }

    fft(even, n / 2, invert);
    fft(uneven, n / 2, invert);

    double ang = 2 * M_PI / n * (invert ? 1 : -1);
    double _Complex w = 1;
    double _Complex wn = cexp(ang * I);

    for (int i = 0; i < n / 2; i++) {
        a[i] = even[i] + w * uneven[i];
        a[i + n / 2] = even[i] - w * uneven[i];
        w *= wn;
    }

    free(even);
    free(uneven);
}

void multiply_fft(const char* x, const char* y) {
    int xlen = strlen(x);
    int ylen = strlen(y);
    int dlina = 1;
    
    while (dlina < xlen + ylen) {
        dlina *= 2;
    }

    double _Complex *p = calloc(dlina, sizeof(double _Complex));
    double _Complex *q = calloc(dlina, sizeof(double _Complex));

    for (int k = 0; k < xlen; k++) {
        p[k] = x[xlen - 1 - k] - '0';
    }
    for (int k = 0; k < ylen; k++) {
        q[k] = y[ylen - 1 - k] - '0';
    }

    fft(p, dlina, 0);
    fft(q, dlina, 0);

    double _Complex *c = calloc(dlina, sizeof(double _Complex));
    for (int k = 0; k < dlina; k++) {
        c[k] = p[k] * q[k];
    }

    fft(c, dlina, 1);

    int *ans = calloc(dlina + 1, sizeof(int));
    for (int k = 0; k < dlina; k++) {
        long long chisl = round(creal(c[k]) / dlina);
        ans[k] += chisl;
        ans[k + 1] += ans[k] / 10; 
        ans[k] %= 10;              
    }

    int max_len = dlina;
    while (max_len > 1 && ans[max_len - 1] == 0) {
        max_len--;
    }

    printf("Multiplication result: ");
    for (int k = max_len - 1; k >= 0; k--) {
        printf("%d", ans[k]);
    }
    printf("\n");

    free(p);
    free(q);
    free(c);
    free(ans);
}

int main() {
    const char* x = "123456789";
    const char* y = "987654321";
    
    multiply_fft(x, y);
    
    return 0;
}
