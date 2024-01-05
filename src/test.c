//
// Created by Evan Chen on 2024/1/6.
//

#include "filter.h"

void test() {
    double previous[5] = {0, 0, 0, 0, 0};
    double input[100];
    for(int i = 0; i < 100; i++) {
        input[i] = i + 1;
    }
    double h[5] = {1, 2, 3, 4, 5};
    // double h[5] = {1, 2, 3, 2, 1};
    double output[100 + 5 - 1];
    /*
    for(int i = 0; i < 10; i++) {
    }
    */
    convolve(output, input, 100, h, 5);
    int a = 0;
}
