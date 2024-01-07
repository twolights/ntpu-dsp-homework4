//
// Created by Evan Chen on 2024/1/6.
//

#include <math.h>
#include "filter.h"
#include "wav_file.h"

void test() {
    double previous[4] = {0, 0, 0, 0 };
    double input[100];
    for(int i = 0; i < 100; i++) {
        input[i] = i + 1;
    }
    double h[5] = {1, 2, 3, 2, 1};
    // double h[5] = {1, 2, 3, 2, 1};
    double buffer[14];
    double output[100 + 5 - 1];
    for(int i = 0; i < 10; i++) {
        int index = i * 10;
        convolve_by_chunk(&output[index], previous, buffer, &input[index], 10, h, 5);
    }
    // convolve(output, input, 100, h, 5);
    int a = 0;
}

void wav_test() {
    WAV_FILE* source = wav_open("/Users/ykchen/Downloads/input.wav");
    WAV_HEADER header = source->header;
    wav_close(source);
    header.sample_hz = 8000;
    header.DATALen = header.sample_hz * 2 * 2 * 10;
    header.total_len = header.DATALen + 36;
    header.bytes_per_sec = header.sample_hz * 2 * 2;
    WAV_FILE* output = wav_open_write("/Users/ykchen/Downloads/output-test.wav", header);
    for(int i = 0; i < 10 * header.sample_hz; i++) {
        int16_t buffer[2] = {0, 0};
        buffer[0] = (int16_t)(10000 * sin(2 * M_PI * 1000 * i / header.sample_hz));
        buffer[1] = (int16_t)(10000 * sin(2 * M_PI * 1000 * i / header.sample_hz));
        fwrite(&buffer, sizeof(int16_t), 2, output->fp);
    }
    wav_close(output);
}