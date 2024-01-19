import os

import numpy as np
import scipy
from scipy.signal import firwin, lfilter

FS = 44100
UPSAMPLE_FACTOR = 80
DOWNSAMPLE_FACTOR = 441
OUTPUT_FS = int(FS * UPSAMPLE_FACTOR / DOWNSAMPLE_FACTOR)
CUTOFF = OUTPUT_FS / 2
ORDER = 256


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


def main():
    file_name = os.path.join(os.path.dirname(__file__), '..', 'input', 'up-is-down-10-sec.wav')
    sr, data = scipy.io.wavfile.read(file_name)
    left, right = data[:, 0], data[:, 1]
    left_upsampled = upsample(left, UPSAMPLE_FACTOR) 
    right_upsampled = upsample(right, UPSAMPLE_FACTOR)
    print(data.shape, sr)
    left_filtered = lpf(left_upsampled, CUTOFF, FS * UPSAMPLE_FACTOR, ORDER)
    right_filtered = lpf(right_upsampled, CUTOFF, FS * UPSAMPLE_FACTOR, ORDER)
    left_downsampled = downsample(left_filtered, DOWNSAMPLE_FACTOR)
    right_downsampled = downsample(right_filtered, DOWNSAMPLE_FACTOR)
    num_samples = left_downsampled.shape[0]
    output = np.column_stack((left_downsampled, right_downsampled))
    scipy.io.wavfile.write('output.wav', OUTPUT_FS, output)
    # output = np.column_stack((left, right))
    # scipy.io.wavfile.write('output.wav', FS, output)


if __name__ == '__main__':
    main()
    