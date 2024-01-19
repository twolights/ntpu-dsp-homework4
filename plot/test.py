import os
import math

import numpy as np
import scipy
from scipy.signal import firwin, lfilter

FS = 44100
UPSAMPLE_FACTOR = 80
DOWNSAMPLE_FACTOR = 441
OUTPUT_FS = int(FS * UPSAMPLE_FACTOR / DOWNSAMPLE_FACTOR)
CUTOFF = OUTPUT_FS / 2
ORDER = 1025

P = DOWNSAMPLE_FACTOR
Q = ORDER
N = 2048


def upsample(data, factor):
    result = np.zeros(len(data) * factor)
    result[::factor] = data
    return result


def downsample(data, factor):
    return data[::factor]


def lpf(data, cutoff, fs, order=5):
    b = scipy.signal.firwin(order, cutoff, window='hamming', fs=fs)
    y = lfilter(b, 1, data)
    return y


def resample_time_domain(data):
    left, right = data[:, 0], data[:, 1]
    left_upsampled = upsample(left, UPSAMPLE_FACTOR)
    right_upsampled = upsample(right, UPSAMPLE_FACTOR)
    left_filtered = lpf(left_upsampled, CUTOFF, FS * UPSAMPLE_FACTOR, ORDER)
    right_filtered = lpf(right_upsampled, CUTOFF, FS * UPSAMPLE_FACTOR, ORDER)
    left_downsampled = downsample(left_filtered, DOWNSAMPLE_FACTOR)
    right_downsampled = downsample(right_filtered, DOWNSAMPLE_FACTOR)
    output = np.column_stack((left_downsampled, right_downsampled))
    return output


def next_power_of_2(x):
    return 1 if x == 0 else 2**math.ceil(math.log2(x))


def resample_fft(data):
    left, right = data[:, 0], data[:, 1]
    lpf_coefficients = scipy.signal.firwin(ORDER, CUTOFF, window='hamming', fs=FS * UPSAMPLE_FACTOR)
    nfft = next_power_of_2(len(left) * UPSAMPLE_FACTOR)
    left_upsampled = upsample(left, UPSAMPLE_FACTOR)
    left_ffted = scipy.fft.fft(left_upsampled, nfft)
    lpf_ffted = scipy.fft.fft(lpf_coefficients, nfft)
    result = left_ffted * lpf_ffted
    output = scipy.fft.ifft(result)
    left_downsampled = downsample(output, DOWNSAMPLE_FACTOR)
    return np.real(left_downsampled)


def main():
    file_name = os.path.join(os.path.dirname(__file__), '..', 'input', 'up-is-down-10-sec.wav')
    _, data = scipy.io.wavfile.read(file_name)
    output = resample_fft(data)
    # output = resample_time_domain(data)
    scipy.io.wavfile.write('output.wav', OUTPUT_FS, output)
    # output = np.column_stack((left, right))
    # scipy.io.wavfile.write('output.wav', FS, output)


if __name__ == '__main__':
    main()
    