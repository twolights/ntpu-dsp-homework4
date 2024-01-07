//
// Created by Evan Chen on 2024/1/5.
//

#include <string.h>
#include <math.h>
#include "filter.h"
#include "resample.h"
#include "wav_file.h"

double** create_channel_buffers(int num_channels, int chunk_size);

void free_channel_buffers(int num_channels, double **channel_buffers);

double* upsample(const double* source, size_t len, int factor) {
    // TODO might wanna reuse the result array
    double* result = (double*)malloc(sizeof(double) * len * factor);
    for(int i = 0; i < len; i++) {
        result[i * factor] = source[i] * factor;
    }
    return result;
}

double* downsample(const double* source, size_t len, int factor) {
    // TODO might wanna reuse the result array
    double* result = (double*)malloc(sizeof(double) * len / factor);
    for(int i = 0; i < len / factor; i++) {
        result[i] = source[i * factor];
    }
    return result;
}

double** create_channel_buffers(int num_channels, int chunk_size) {
    double** channel_buffers = (double**)malloc(sizeof(double*) * num_channels * chunk_size);
    for(int i = 0; i < num_channels; i++) {
        channel_buffers[i] = (double*)malloc(sizeof(double) * chunk_size);
    }
    return channel_buffers;
}

void free_channel_buffers(int num_channels, double **channel_buffers) {
    for(int i = 0; i < num_channels; i++) {
        free(channel_buffers[i]);
    }
    free(channel_buffers);
}

void resample_wave_file(WAV_FILE* wav_file,
                        int upsample_factor,
                        int downsample_factor,
                        int lpf_order_M) {
    int i, j, channel;
    size_t order = get_order_by_M(lpf_order_M);
    double source_Fs = wav_file->header.sample_hz,
        lpf_Fs = source_Fs * upsample_factor,
        target_Fs = lpf_Fs / downsample_factor;
    int num_channels = wav_file->header.channels;
    int chunk_size = (int)source_Fs,
        upsampled_chuck_size = chunk_size * upsample_factor,
        downsampled_chunk_size = upsampled_chuck_size / downsample_factor;
    double* lpf = create_lowpass_filter(target_Fs / 2, lpf_Fs, order);
    // double* lpf = create_lowpass_filter(target_Fs / 2, lpf_Fs, order);
    double** channel_buffers = create_channel_buffers(num_channels, chunk_size);
    int num_to_read = num_channels * chunk_size;
    int16_t* buffer = (int16_t*)malloc(sizeof(int16_t) * num_to_read);
    WAV_HEADER header = wav_file->header;   // TODO change sampling rate here
    WAV_FILE* output_file;
    int count = 0;
    double* convolution_buffer = (double*)malloc(sizeof(double) * (chunk_size * upsample_factor + order - 1));
    double** previous_buffers = (double**)malloc(sizeof(double*) * num_channels);
    // double* previous_buffer = (double*)malloc(sizeof(double) * (order - 1));
    double** convolution_output = (double**)malloc(sizeof(double*) * num_channels);
    double** downsampled_output = (double**)malloc(sizeof(double*) * num_channels);
    for(i = 0; i < num_channels; i++) {
        convolution_output[i] = (double*)malloc(sizeof(double) * chunk_size);
        previous_buffers[i] = (double*)malloc(sizeof(double) * (order - 1));
        memset(previous_buffers[i], 0, sizeof(double) * (order - 1));
    }

    header.sample_hz = target_Fs;
    header.bytes_per_sec = target_Fs * header.sample_bits / 8 * num_channels;
    header.DATALen = 320000;
    header.total_len = header.DATALen + 36;
    strncpy(header.chDATA, "data" ,4);
    output_file = wav_open_write("output.wav", header);
    while(!feof(wav_file->fp) && count < 10) {
        count++;
        wav_read(wav_file, buffer, num_to_read);
        for(i = 0; i < num_to_read; i++) {
            channel = i % num_channels;
            channel_buffers[channel][i / num_channels] = buffer[i];
        }
        for(i = 0; i < num_channels; i++) {
            double* upsampled = upsample(channel_buffers[i], chunk_size, upsample_factor);
            convolve_by_chunk(convolution_output[i], previous_buffers[i], convolution_buffer,
                              upsampled, upsampled_chuck_size,
                              lpf, order);
            // double* downsampled = downsample(upsampled, upsampled_chuck_size, downsample_factor);
            double* downsampled = downsample(convolution_output[i], upsampled_chuck_size, downsample_factor);
            free(upsampled);  // TODO reuse upsample & downsample buffer
            downsampled_output[i] = downsampled;
        }
        wav_write(output_file, downsampled_output, downsampled_chunk_size);
        for(i = 0; i < num_channels; i++) {
            free(downsampled_output[i]);
        }
        printf("Iteration %d complete\n", count);
    }

    free_channel_buffers(num_channels, channel_buffers);
    free(lpf);
    for(i = 0; i < num_channels; i++) {
        free(convolution_output[i]);
        free(previous_buffers[i]);
    }
    free(convolution_buffer);
    free(previous_buffers);
    free(downsampled_output);
    wav_close(output_file);
}
