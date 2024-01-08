//
// Created by Evan Chen on 2024/1/5.
//

#include <math.h>
#include <string.h>
#include <stdio.h>
#include "filter.h"

size_t get_order_by_M(int M) {
    return (size_t)(2 * M + 1);
}

double* hamming_window(size_t order) {
    double* window = (double*)malloc(sizeof(double) * order);
    for(int i = 0; i < order; i++) {
        window[i] = 0.54 - 0.46 * cos(M_PI * 2 * i / (double)((int)order - 1));
    }
    return window;
}

double* create_lowpass_filter(int cutoff_frequency, int sample_rate, size_t order) {
    double* result = (double*)malloc(sizeof(double) * order);
    double omega_c = cutoff_frequency * M_PI * 2 / sample_rate;
    double* window = hamming_window(order);
    int M = (order - 1) / 2;
    double a;
    for(int i = 0; i < order; i++) {
        if(i == M) {
            result[i] = omega_c / M_PI;
            continue;
        }
        a = (i - M);
        result[i] = sin(a * omega_c) / (a * M_PI) * window[i];
    }
    free(window);
    return result;
}

void save_lowpass_filter_(double* filter, size_t order, const char* filename) {
    FILE* fp = fopen(filename, "w");
    for(int i = 0; i < order; i++) {
        fprintf(fp, "%f\n", filter[i]);
    }
    fclose(fp);
}

void convolve(double* output,
              double* x, size_t x_len,
              double* h, size_t h_len) {
    size_t output_len = x_len + h_len - 1;
    for(int i = 0; i < output_len; i++) {
        output[i] = 0;
        for(int j = 0; j < h_len; j++) {
            int h_reversed = h_len - j - 1, index = i - h_reversed;
            if(index < 0 || index >= x_len) {
                continue;
            }
            output[i] += x[index] * h[h_reversed];
        }
    }
}

void convolve_by_chunk(double* output, double* previous, double* buffer,
                       double* x, size_t x_len,
                       double* h, size_t h_len) {
    convolve(buffer, x, x_len, h, h_len);
    memcpy((void*)output, (void*)buffer, sizeof(double) * x_len);
    for(int i = 0; i < h_len - 1; i++) {
        output[i] += previous[i];
        previous[i] = buffer[x_len + i];
    }
}
