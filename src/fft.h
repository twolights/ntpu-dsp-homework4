//
// Created by Evan Chen on 2024/1/11.
//

#ifndef FFT_H
#define FFT_H

#include <complex.h>

complex double* create_fft_buffer(int n);
void fill_fft_buffer_int16(complex double* buffer, const int16_t* data, int size);
void fill_fft_buffer_double(complex double* buffer, const double* data, int size);

void fft(complex double* a, int n);
void ifft(complex double* a, int n);

#endif //FFT_H
