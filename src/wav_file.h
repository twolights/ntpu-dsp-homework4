//
// Created by Evan Chen on 2024/1/5.
//

#ifndef WAV_FILE_H
#define WAV_FILE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct WAV_HEADER {
    char chRIFF[4];                 // RIFF tag
    int32_t  total_Len;             // Total length of the file (header + audio) = 36 + dataSize
    char chWAVE[4];                 // WAVE tag
    char chFMT[4];                  // fmt tag
    int32_t FMTLen;
    int16_t fmt_pcm;                // Format category: 1 (PCM)
    int16_t channels;               // Number of channels
    int32_t sample_hz;              // Sampling points per second
    int32_t bytes_per_sec;          // Bit rate = sampling frequency * bit depth / 8
    int16_t sample_size;            // Size of a multi-channel sample block (bytes)
    int16_t sample_bits;            // Sampling bit depth (m)
    char chDATA[4];                 // data tag
    int32_t  DATALen;               // Size of the audio data
} WAV_HEADER;

typedef struct WAV_FILE {
    FILE* fp;
    WAV_HEADER header;
} WAV_FILE;

WAV_FILE* wav_open(const char* filename);
void wav_read(WAV_FILE* wav_file, int16_t* buffer, int num_samples);

WAV_FILE* wav_open_write(const char* filename, WAV_HEADER header);
void wav_write(WAV_FILE* wav_file, double** channel_buffers, int chunk_size);

void wav_close(WAV_FILE* wav_file);

#endif //WAV_FILE_H