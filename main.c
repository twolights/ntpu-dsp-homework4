#include <stdio.h>
#include "wav_file.h"
#include "resample.h"
#include "filter.h"

#define ORDER_M 512
#define SOURCE_SAMPLING_RATE 44100
#define TARGET_SAMPLING_RATE 8000
#define FILTER_CUTOFF_FREQUENCY (TARGET_SAMPLING_RATE / 2)
#define UPSAMPLE_FACTOR 80
#define DOWNSAMPLE_FACTOR 441

#define INPUT_FILENAME "./input/up-is-down-trimmed.wav"

void test();

int main() {
    WAV_FILE* wav_file = wav_open(INPUT_FILENAME);
    resample_wave_file(wav_file,
                       UPSAMPLE_FACTOR,
                       DOWNSAMPLE_FACTOR,
                       ORDER_M);
    wav_close(wav_file);
    // test();
}
