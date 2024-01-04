% vim: syntax=matlab

clc;
clear;
close all;


L = 80;
M = 441;
O_Fs = 44100 * L / M;
Fs = 44100;
M_ORDER = 1024;

[x, Fs] = audioread('/Users/ykchen/Projects/ykchen/ntpu/DSP/HW4/input/up-is-down.wav');

left = x(:,1);
right = x(:,1);
left_upsampled = upsample(left, L) .* L;
right_upsampled = upsample(right, L) .* L;

lpf = fir1(M_ORDER, 1 / (O_Fs / 2));

left_upsampled_lpfed = filter(lpf, 1, left_upsampled);
right_upsampled_lpfed = filter(lpf, 1, right_upsampled);

left_downsampled = downsample(left_upsampled_lpfed, M);
right_downsampled = downsample(right_upsampled_lpfed, M);
output = cat(2, left_downsampled, right_downsampled);
audiowrite('/Users/ykchen/Downloads/output.wav', output, O_Fs);

% [x, Fs] = audioread('/Users/ykchen/Projects/ykchen/ntpu/DSP/HW4/input/up-is-down.wav');
% y = resample(x, 8000, 44100);
% audiowrite('/Users/ykchen/Downloads/output.wav', y, 8000);
