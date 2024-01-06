//
// Created by Evan Chen on 2024/1/5.
//

#include "filter.h"
#include "resample.h"
#include "wav_file.h"

int16_t* upsample(const int16_t* source, size_t len, int factor) {
    // TODO might wanna reuse the result array
    int16_t* result = (int16_t*)malloc(sizeof(int16_t) * len * factor);
    for(int i = 0; i < len; i++) {
        result[i * factor] = source[i];
    }
    return result;
}

int16_t* downsample(const int16_t* source, size_t len, int factor) {
    // TODO might wanna reuse the result array
    int16_t* result = (int16_t*)malloc(sizeof(int16_t) * len / factor);
    for(int i = 0; i < len / factor; i++) {
        result[i] = source[i * factor];
    }
    return result;
}

void resample_wave_file(WAV_FILE* wav_file,
                        int upsample_factor,
                        int downsample_factor,
                        int lpf_order_M) {
    size_t order = get_order_by_M(lpf_order_M);
    double source_Fs = wav_file->header.sample_hz,
        lpf_Fs = source_Fs * upsample_factor,
        target_Fs = lpf_Fs / downsample_factor;
    double* lpf = create_lowpass_filter(target_Fs / 2, lpf_Fs, order);
    free(lpf);
}
