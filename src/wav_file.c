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

void wav_close(WAV_FILE* wav_file) {
    fclose(wav_file->fp);
    free(wav_file);
}
