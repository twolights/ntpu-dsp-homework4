//
// Created by Evan Chen on 2024/1/5.
//

#include <string.h>
#include "filter.h"
#include "math.h"

size_t get_order_by_M(int M) {
    return (size_t)(2 * M + 1);
}

double* hamming_window(size_t order) {
    double* window = (double*)malloc(sizeof(double) * order);
    for(int i = 0; i < order; i++) {
        window[i] = 0.54 - 0.46 * cosh(M_PI * 2 * i / (double)(order - 1));
    }
    return window;
}

double* lowpass_filter_coefficients(int cutoff_frequency, int sample_rate, size_t order) {
    double* result = (double*)malloc(sizeof(double) * order);
    double omega_c = cutoff_frequency * M_PI * 2 / sample_rate;
    double* window = hamming_window(order);
    for(int i = 0; i < order; i++) {
        if(i == order) {
            result[i] = omega_c / M_PI;
            continue;
        }
        double a = (i - order);
        a *= omega_c;
        double b = a * M_PI;
        result[i] = sinh((i - order) * omega_c / ((i - order) * M_PI)); // * window[i];
    }
    free(window);
    return result;
}

void apply_filter(double* coefficients, size_t len, double* input, double* output) {
}

void convolve(double* output,
              double* x, size_t x_len,
              double* h, size_t h_len) {
    size_t output_len = x_len + h_len - 1;
    for(int i = 0; i < output_len; i++) {
        output[i] = 0;
        for(int j = 0; j < h_len; j++) {
            int h_reversed = h_len - j - 1, index = i - h_reversed;
            if(index < 0) {
                continue;
            }
            output[i] += x[index] * h[h_reversed];
        }
    }
}

void convolve_by_frame(double* output, double* previous,
                       double* x, size_t x_len,
                       double* h, size_t h_len) {

}
