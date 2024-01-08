//
// Created by Evan Chen on 2024/1/5.
//

#ifndef RESAMPLE_H
#define RESAMPLE_H

#include <stdlib.h>
#include "wav_file.h"

void upsample(const double* source, size_t len, int factor, double* result);
void downsample(const double* source, size_t len, int factor, double* result);

void resample_wave_file(WAV_FILE* wav_file,
                        int upsample_factor,
                        int downsample_factor,
                        int lpf_order_M);

#endif //RESAMPLE_H
