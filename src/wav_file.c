//
// Created by Evan Chen on 2024/1/5.
//
#include "wav_file.h"

WAV_FILE* wav_open(const char* filename) {
    WAV_FILE* wav_file = (WAV_FILE*)malloc(sizeof(WAV_FILE));
    wav_file->fp = fopen(filename, "rb");
    if(wav_file->fp == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }
    fread(&wav_file->header, sizeof(WAV_HEADER), 1, wav_file->fp);
    return wav_file;
}

void wav_read(WAV_FILE* wav_file, int16_t* buffer, int num_samples) {
    fread(buffer, sizeof(int16_t), num_samples, wav_file->fp);
}

WAV_FILE* wav_open_write(const char* filename, WAV_HEADER header) {
    WAV_FILE* wav_file = (WAV_FILE*)malloc(sizeof(WAV_FILE));
    wav_file->header = header;
    wav_file->fp = fopen(filename, "wb");
    if(wav_file->fp == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }
    fwrite(&header, sizeof(WAV_HEADER), 1, wav_file->fp);
    return wav_file;
}

void wav_write(WAV_FILE* wav_file, double** channel_buffers, int chunk_size) {
    int num_channels = wav_file->header.channels;
    int i, channel;
    int16_t buffer;
    for(i = 0; i < chunk_size; i++) {
        for(channel = 0; channel < num_channels; channel++) {
            buffer = (int16_t)channel_buffers[channel][i];
            fwrite(&buffer, sizeof(int16_t), 1, wav_file->fp);
        }
    }
}

void wav_close(WAV_FILE* wav_file) {
    fclose(wav_file->fp);
    free(wav_file);
}
