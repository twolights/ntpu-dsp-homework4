//
// Created by Evan Chen on 2024/1/5.
//

#ifndef RESAMPLE_H
#define RESAMPLE_H

#include <stdlib.h>

int16_t* upsample(const int16_t* source, size_t len, int factor);
int16_t* downsample(const int16_t* source, size_t len, int factor);

#endif //RESAMPLE_H
