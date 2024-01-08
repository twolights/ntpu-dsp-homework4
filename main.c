#include "wav_file.h"
#include "resample.h"
#include "filter.h"

#define ORDER_M 1024
#define UPSAMPLE_FACTOR 80
#define DOWNSAMPLE_FACTOR 441
#define SOURCE_SAMPLE_RATE 44100
#define LPF_COEFFICIENTS_OUTPUT_FILENAME "./output/lpf.csv"

void save_lpf() {
    int target_Fs = SOURCE_SAMPLE_RATE * UPSAMPLE_FACTOR / DOWNSAMPLE_FACTOR,
            lpf_Fs = SOURCE_SAMPLE_RATE * UPSAMPLE_FACTOR;
    int order = get_order_by_M(ORDER_M);
    double* lpf = create_lowpass_filter(target_Fs / 2, lpf_Fs, order);
    save_lowpass_filter_(lpf, order, LPF_COEFFICIENTS_OUTPUT_FILENAME);
    free(lpf);
}

int main(int argc, const char* argv[]) {
    if(argc < 2) {
        printf("Usage: %s <input.wav> <output.wav>\n", argv[0]);
        return 1;
    }
    const char* filename = argv[1];
    printf("Processing %s...\n", filename);
    WAV_FILE* wav_file = wav_open(filename);
    resample_wave_file(wav_file,
                       argv[2],
                       UPSAMPLE_FACTOR,
                       DOWNSAMPLE_FACTOR,
                       ORDER_M);
    wav_close(wav_file);
    save_lpf();
    return 0;
}
