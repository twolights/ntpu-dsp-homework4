#include "wav_file.h"
#include "resample.h"

#define ORDER_M 512
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
    // wav_test();
}
