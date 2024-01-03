import matplotlib.pyplot as plt
import os.path
from typing import Tuple

import numpy as np
import scipy
import functools

SOURCE_SAMPLING_RATE = 44100
TARGET_SAMPLING_RATE = 8000

UPSAMPLE_FACTOR = 10
# UPSAMPLE_FACTOR = 80
DOWNSAMPLE_FACTOR = 441


def upsample(data: np.ndarray, factor: int) -> np.ndarray:
    num_samples, num_channels = data.shape
    num_samples *= factor
    z = np.zeros((num_samples, num_channels))
    z[::factor] = data
    return z


def butter_lowpass(Fc: float, Fs: float, M: int) -> Tuple:
    return scipy.signal.butter(M, Fc, fs=Fs, btype='low', analog=False)


def butter_lowpass_filter(Fc: float, Fs: float, M: int, x: np.ndarray):
    a, b = butter_lowpass(Fc, Fs, M)
    return scipy.signal.lfilter(b, a, x)


def main():
    a = np.array([1, 2, 3, 4, 5, 6, 7, 8, 5, 10, 15, 20, 25, 30, 35, 40]).reshape((8, 2))
    u = upsample(a, 5)
    print(u)
    file_name = os.path.join(os.path.dirname(__file__), '..', 'input', 'up-is-down.wav')
    sr, data = scipy.io.wavfile.read(file_name)
    data = data[:44100 * 10]
    # Fc = SOURCE_SAMPLING_RATE
    # Fs = SOURCE_SAMPLING_RATE * UPSAMPLE_FACTOR
    Fc = 10000
    Fs = SOURCE_SAMPLING_RATE
    upsampled = upsample(data, UPSAMPLE_FACTOR)
    # upsampled = upsampled[:UPSAMPLE_FACTOR * 100000]

    LPF = functools.partial(butter_lowpass_filter, Fc, Fs, 512)

    # LPF = functools.partial(butter_lowpass_filter, SOURCE_SAMPLING_RATE, SOURCE_SAMPLING_RATE * UPSAMPLE_FACTOR, 16)
    # channel0, channel1 = upsampled[:, 0], upsampled[:, 1]
    # channel0, channel1 = LPF(channel0), LPF(channel1)
    # upsampled[:, 0] = channel0
    # upsampled[:, 1] = channel1
    # upsampled *= UPSAMPLE_FACTOR
    # scipy.io.wavfile.write('test.wav', SOURCE_SAMPLING_RATE * UPSAMPLE_FACTOR, upsampled)
    channel0, channel1 = data[:, 0], data[:, 1]
    channel0, channel1 = LPF(channel0), LPF(channel1)
    new = np.ndarray(shape=data.shape, dtype='int16')
    new[:, 0] = channel0 * 50
    new[:, 1] = channel1 * 50
    scipy.io.wavfile.write('new.wav', SOURCE_SAMPLING_RATE, new)
    scipy.io.wavfile.write('source.wav', SOURCE_SAMPLING_RATE, data)


if __name__ == '__main__':
    main()
