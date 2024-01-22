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
        result[i * factor] = source[i]; // * factor;
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

void free_frame_buffers(int num_channels, double** channel_buffers) {
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

complex double** prepare_previous_buffers(int num_channels, size_t previous_buffer_size) {
    complex double** result = (complex double**)malloc(sizeof(complex double*) * num_channels);
    for(int i = 0; i < num_channels; i++) {
        result[i] = (complex double*)malloc(sizeof(complex double) * previous_buffer_size);
        memset(result[i], 0, sizeof(complex double) * previous_buffer_size);
    }
    return result;
}

void free_previous_buffers(int num_channels, complex double** previous_buffers) {
    for(int i = 0; i < num_channels; i++) {
        free(previous_buffers[i]);
    }
    free(previous_buffers);
}

void perform_chunked_fft(double* frame_buffer, int frame_size,
                         const complex double* lpf_ffted, int lpf_order,
                         double* upsampled, int upsample_factor,
                         double* downsampled, int downsample_factor,
                         complex double* chunk, int upsampled_chuck_size, int downsampled_chunk_size,
                         complex double* previous_buffer, int previous_buffer_size,
                         int n_fft,
                         double* output_buffer) {
    int i, j, start;
    int num_to_take = downsample_factor + lpf_order - 1;
    memset(output_buffer, 0, sizeof(double) * upsample_factor);

    upsample(frame_buffer, frame_size, upsample_factor, upsampled);
    for(i = 0; i < upsample_factor; i++) {
        memset(chunk, 0, sizeof(complex double) * n_fft);
        fill_fft_buffer_double(chunk, &upsampled[i * downsample_factor], downsample_factor);
        fft(chunk, n_fft);
        for(j = 0; j < n_fft; j++) {
            chunk[j] *= lpf_ffted[j];
        }
        ifft(chunk, n_fft);
        start = i * downsample_factor;

        for(j = 0; j < previous_buffer_size; j++) {
            chunk[j] += previous_buffer[j];
        }

        for(j = 0; j < previous_buffer_size; j++) {
            previous_buffer[j] = chunk[downsample_factor + j];
        }

        for(j = 0; j < num_to_take; j++) {
            output_buffer[start + j] = creal(chunk[j]);
        }
        int m = 0;
    }
    downsample(output_buffer, upsampled_chuck_size, downsample_factor, downsampled);
    int k = 0;
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
            downsampled_chunk_size = upsampled_chuck_size / downsample_factor,
            previous_buffer_size = downsample_factor + lpf_order - 1 - downsample_factor;
    int num_to_read = num_channels * frame_size;
    complex double* lpf_ffted = create_fft_buffer(FFT_SIZE);

    int16_t* input_buffer = (int16_t*)malloc(sizeof(int16_t) * num_to_read);
    complex double** previous_buffers = prepare_previous_buffers(num_channels, previous_buffer_size);
    complex double* chunk = create_fft_buffer(FFT_SIZE);
    double* output_buffer = (double*)malloc(sizeof(double) * upsample_factor);
    double** frame_buffer = prepare_frame_buffer(num_channels, frame_size);     // TODO
    double* upsampled = (double*)malloc(sizeof(double) * frame_size * upsample_factor);;
    double** downsampled_output = prepare_downsampled_output(num_channels,
                                                             upsampled_chuck_size,
                                                             downsample_factor);

    WAV_FILE* output_file = wav_open_write(output_filename, header);

    for(i = 0; i < lpf_order; i++) {
        lpf[i] = lpf[i] * upsample_factor;
    }
    fill_fft_buffer_double(lpf_ffted, lpf, lpf_order);
    fft(lpf_ffted, FFT_SIZE);

    // fseek(wav_file->fp, wav_file->header.DATALen + sizeof(int16_t) * 4, SEEK_CUR);
    while(!feof(wav_file->fp)) {
        count++;
        wav_read(wav_file, input_buffer, num_to_read);
        for(i = 0; i < num_to_read; i++) {
            channel = i % num_channels;
            frame_buffer[channel][i / num_channels] = input_buffer[i];
        }
        for(i = 0; i < num_channels; i++) {
            perform_chunked_fft(frame_buffer[i], frame_size,
                                lpf_ffted, lpf_order,
                                upsampled, upsample_factor,
                                downsampled_output[i], downsample_factor,
                                chunk, upsampled_chuck_size, downsampled_chunk_size,
                                previous_buffers[i], previous_buffer_size,
                                FFT_SIZE,
                                output_buffer);
            int j = 0;
        }
        wav_write(output_file, downsampled_output, downsampled_chunk_size);
        printf("Iteration %d complete\n", count);
    }
    wav_close(output_file);

    free(input_buffer);
    free(chunk);
    free_frame_buffers(num_channels, frame_buffer);
    free(upsampled);
    free_downsampled_output(num_channels, downsampled_output);
    free_previous_buffers(num_channels, previous_buffers);
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
    FILE* fp = fopen("lpf.txt", "w");
    for(int i = 0; i < order; i++) {
        fprintf(fp, "%f\n", lpf[i]);
    }
    fclose(fp);
    prepare_output_header(target_Fs, num_channels, num_samples, &output_header);
    perform_fft_filter(wav_file, source_Fs,
                       output_header, output_filename,
                       lpf, order,
                       upsample_factor, downsample_factor);
    free(lpf);
}
