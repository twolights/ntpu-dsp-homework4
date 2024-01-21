//
// Created by Evan Chen on 2024/1/5.
//

#include <string.h>
#include "filter.h"
#include "resample.h"
#include "wav_file.h"
#include "fft.h"

#define FFT_SIZE 2048


void upsample(const double* source, size_t len, int factor, double* result) {
    memset(result, 0, sizeof(double) * len * factor);
    for(int i = 0; i < len; i++) {
        result[i * factor] = source[i] * factor;
    }
}

void downsample(const double* source, size_t len, int factor, double* result) {
    for(int i = 0; i < len / factor; i++) {
        result[i] = source[i * factor];
    }
}

double** prepare_frame_buffer(int num_channels, int chunk_size) {
    double** channel_buffers = (double**)malloc(sizeof(double*) * num_channels * chunk_size);
    for(int i = 0; i < num_channels; i++) {
        channel_buffers[i] = (double*)malloc(sizeof(double) * chunk_size);
    }
    return channel_buffers;
}

void free_channel_buffers(int num_channels, double** channel_buffers) {
    for(int i = 0; i < num_channels; i++) {
        free(channel_buffers[i]);
    }
    free(channel_buffers);
}

void prepare_output_header(double target_Fs, int num_channels, size_t num_samples, WAV_HEADER *header) {
    header->sample_hz = target_Fs;
    header->bytes_per_sec = target_Fs * header->sample_bits / 8 * num_channels;
    header->DATALen = num_samples * header->bytes_per_sec;
    header->total_len = header->DATALen + 36;
    strncpy(header->chDATA, "data", 4);
}

double** prepare_downsampled_output(int num_channels, int source_len, int factor) {
    double** result = (double**)malloc(sizeof(double*) * num_channels);
    for(int i = 0; i < num_channels; i++) {
        result[i] = (double*)malloc(sizeof(double) * source_len / factor);
    }
    return result;
}

void free_downsampled_output(int num_channels, double** downsampled_output) {
    for(int i = 0; i < num_channels; i++) {
        free(downsampled_output[i]);
    }
    free(downsampled_output);
}

void perform_chunked_fft(double* frame_buffer, int frame_size,
                         const complex double* lpf_ffted,
                         double* upsampled, int upsample_factor,
                         double* downsampled, int downsample_factor,
                         complex double* buffer,
                         complex double* previous_buffer, int n_fft) {
    int upsampled_chuck_size = frame_size * upsample_factor;
    int i;
    upsample(frame_buffer, frame_size, upsample_factor, upsampled);
    fill_fft_buffer_double(convolution_buffer, upsampled, upsampled_chuck_size);
    fft(convolution_buffer, FFT_SIZE);
    for(i = 0; i < FFT_SIZE; i++) {
        convolution_buffer[i] *= lpf_ffted[i];
    }
    ifft(convolution_buffer, FFT_SIZE);
    for(i = 0; i < upsampled_chuck_size; i++) {
        convolution_output[i] = convolution_buffer[i] + previous_buffer[i];
        previous_buffer[i] = convolution_buffer[i + upsampled_chuck_size];
    }
    free(upsampled);
    free(convolution_output);
}

void perform_fft_filter(WAV_FILE* wav_file, double source_Fs,
                        WAV_HEADER header, const char *output_filename,
                        double *lpf, size_t lpf_order,
                        int upsample_factor,
                        int downsample_factor) {
    int i, channel, count = 0;
    int num_channels = wav_file->header.channels;
    int frame_size = (int)downsample_factor,
            upsampled_chuck_size = frame_size * upsample_factor,
            downsampled_chunk_size = upsampled_chuck_size / downsample_factor;
    int num_to_read = num_channels * frame_size;
    complex double* lpf_ffted = create_fft_buffer(FFT_SIZE);

    int16_t* input_buffer = (int16_t*)malloc(sizeof(int16_t) * num_to_read);
    complex double* buffer = create_fft_buffer(FFT_SIZE);
    double* convolution_output = (double*)malloc(sizeof(double) * upsampled_chuck_size);
    double** frame_buffer = prepare_frame_buffer(num_channels, frame_size);
    double* convolution_buffer = (double*)malloc(sizeof(double) * (frame_size * upsample_factor + lpf_order - 1));
    double** previous_buffers = (double**)malloc(sizeof(double*) * num_channels);
    double* upsampled = (double*)malloc(sizeof(double) * frame_size * upsample_factor);;
    double** downsampled_output = prepare_downsampled_output(num_channels,
                                                             upsampled_chuck_size,
                                                             downsample_factor);

    WAV_FILE* output_file = wav_open_write(output_filename, header);

    fill_fft_buffer_double(lpf_ffted, lpf, lpf_order);
    fft(lpf_ffted, FFT_SIZE);

    for(i = 0; i < num_channels; i++) {
        previous_buffers[i] = (double*)malloc(sizeof(double) * (lpf_order - 1));
        memset(previous_buffers[i], 0, sizeof(double) * (lpf_order - 1));
    }

    while(!feof(wav_file->fp)) {
        count++;
        wav_read(wav_file, input_buffer, num_to_read);
        for(i = 0; i < num_to_read; i++) {
            channel = i % num_channels;
            frame_buffer[channel][i / num_channels] = input_buffer[i];
        }
        for(i = 0; i < num_channels; i++) {
            upsample(frame_buffer[i], frame_size, upsample_factor, upsampled);
            downsample(convolution_output, upsampled_chuck_size, downsample_factor, downsampled_output[i]);
        }
        wav_write(output_file, downsampled_output, downsampled_chunk_size);
        printf("Iteration %d complete\n", count);
    }
    wav_close(output_file);

    for(i = 0; i < num_channels; i++) {
        free(previous_buffers[i]);
    }
    free(input_buffer);
    free(convolution_output);
    free_channel_buffers(num_channels, frame_buffer);
    free(convolution_buffer);
    free(previous_buffers);
    free(upsampled);
    free_downsampled_output(num_channels, downsampled_output);
    free(lpf_ffted);
}

void resample_wave_file(WAV_FILE* wav_file,
                        const char* output_filename,
                        int upsample_factor,
                        int downsample_factor,
                        int lpf_order_M) {
    size_t order = get_order_by_M(lpf_order_M);
    double source_Fs = wav_file->header.sample_hz,
        lpf_Fs = source_Fs * upsample_factor,
        target_Fs = lpf_Fs / downsample_factor;
    int num_channels = wav_file->header.channels;
    double* lpf = create_lowpass_filter(target_Fs / 2, lpf_Fs, order);
    size_t num_samples = wav_get_num_samples(wav_file);
    WAV_HEADER output_header = wav_file->header;
    prepare_output_header(target_Fs, num_channels, num_samples, &output_header);
    perform_fft_filter(wav_file, source_Fs,
                       output_header, output_filename,
                       lpf, order,
                       upsample_factor, downsample_factor);
    free(lpf);
}
