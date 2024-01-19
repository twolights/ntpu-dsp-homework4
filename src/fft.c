//
// Created by Evan Chen on 2024/1/11.
//

#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "fft.h"


void fft(complex double* a, int n) {
    int i;
    complex double t;
    if(n <= 1) {
        return;
    }

    complex double* a0 = (complex double*)malloc(sizeof(complex double) * n / 2);
    complex double* a1 = (complex double*)malloc(sizeof(complex double) * n / 2);

    for(i = 0; i < (n / 2); i++) {
        a0[i] = a[i * 2];
        a1[i] = a[i * 2 + 1];
    }

    fft(a0, n / 2);
    fft(a1, n / 2);

    for(i = 0; i < (n / 2); i++) {
        t = cexp(-2.0 * I * M_PI * i / n) * a1[i];
        a[i] = a0[i] + t;
        a[i + n / 2] = a0[i] - t;
    }

    free(a0);
    free(a1);
}

void ifft(complex double* a, int n) {
    int i;
    complex double t;
    if(n <= 1) {
        return;
    }

    complex double* a0 = (complex double*)malloc(sizeof(complex double) * n / 2);
    complex double* a1 = (complex double*)malloc(sizeof(complex double) * n / 2);

    for(i = 0; i < n / 2; i++) {
        a0[i] = a[i * 2];
        a1[i] = a[i * 2 + 1];
    }

    ifft(a0, n / 2);
    ifft(a1, n / 2);

    for(i = 0; i < (n / 2); i++) {
        t = cexp(2.0 * I * M_PI * i / n) * a1[i];
        a[i] = a0[i] + t;
        a[i + n / 2] = a0[i] - t;
    }

    for(i = 0; i < n; i++) {
        a[i] /= 2;
    }

    free(a0);
    free(a1);
}