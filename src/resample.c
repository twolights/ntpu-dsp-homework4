//
// Created by Evan Chen on 2024/1/5.
//

#include "filter.h"
#include "resample.h"

int16_t* upsample(const int16_t* source, size_t len, int factor) {
    int16_t* result = (int16_t*)malloc(sizeof(int16_t) * len * factor);
    for(int i = 0; i < len; i++) {
        result[i * factor] = source[i];
    }
    return result;
}

int16_t* downsample(const int16_t* source, size_t len, int factor) {
    int16_t* result = (int16_t*)malloc(sizeof(int16_t) * len / factor);
    for(int i = 0; i < len / factor; i++) {
        result[i] = source[i * factor];
    }
    return result;
}
