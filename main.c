#include <stdio.h>
#include "wav_file.h"
#include "resample.h"
#include "filter.h"

#define ORDER_M 512
#define SOURCE_SAMPLING_RATE 44100
#define TARGET_SAMPLING_RATE 8000
#define FILTER_ORDER 512
#define FILTER_CUTOFF_FREQUENCY (TARGET_SAMPLING_RATE / 2)
#define UPSAMPLE_FACTOR 80
#define DOWNSAMPLE_FACTOR 441

#define INPUT_FILENAME "./input/up-is-down-trimmed.wav"

void test();

int main() {
    /*
//    WAV_FILE* wav_file = wav_open(INPUT_FILENAME);
//    wav_close(wav_file);
    size_t order = get_order_by_M(ORDER_M);
    double* coefficients = lowpass_filter_coefficients(TARGET_SAMPLING_RATE,
                                                       SOURCE_SAMPLING_RATE,
                                                       order);
    for(int i = 0; i < order; i++) {
        printf("%lf\n", coefficients[i]);
    }
    return 0;
    */
    test();
}
