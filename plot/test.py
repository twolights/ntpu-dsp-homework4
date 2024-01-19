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
    output = np.zeros(int(len(left) * UPSAMPLE_FACTOR / DOWNSAMPLE_FACTOR))
    num_frames = math.ceil(len(left) / DOWNSAMPLE_FACTOR)

    nfft = next_power_of_2(DOWNSAMPLE_FACTOR * UPSAMPLE_FACTOR)
    lpf_coefficients = scipy.signal.firwin(ORDER, CUTOFF, window='hamming', fs=FS * UPSAMPLE_FACTOR)
    lpf_padded = np.pad(lpf_coefficients, (0, nfft - len(lpf_coefficients)))
    lpf_padded_ffted = scipy.fft.fft(lpf_padded)
    # lpf_padded = np.pad(lpf_coefficients, (0, N - len(lpf_coefficients)))

    temp_buffer = np.zeros(nfft, dtype=np.complex64)
    
    for i in range(0, num_frames):
        frame = left[i * DOWNSAMPLE_FACTOR:(i + 1) * DOWNSAMPLE_FACTOR]
        frame_upsampled = upsample(frame, UPSAMPLE_FACTOR)
        frame_padded = np.pad(frame_upsampled, (0, nfft - len(frame_upsampled)))
        # frame_padded = np.pad(frame, (0, N - len(frame)))
        frame_ffted = scipy.fft.fft(frame_padded)
        result = frame_ffted * lpf_padded_ffted
        frame_output = scipy.fft.ifft(result)
        frame_downsampled = downsample(frame_output, DOWNSAMPLE_FACTOR)
        frame_downsampled += temp_buffer[:frame_downsampled.shape[0]]
        temp_buffer[:frame_downsampled.shape[0]] = 0
        np.roll(temp_buffer, -1 * frame_downsampled.shape[0])
        # frame_downsampled[:UPSAMPLE_FACTOR] += temp_buffer[:UPSAMPLE_FACTOR]
        saved_length = frame_downsampled.shape[0] - UPSAMPLE_FACTOR
        temp_buffer[:saved_length] = frame_downsampled[UPSAMPLE_FACTOR:]
        if ((i + 1) * UPSAMPLE_FACTOR) > len(output):
            output[-1 * frame_downsampled.shape[0]:] = np.real(frame_downsampled)
        else:
            output[i * UPSAMPLE_FACTOR:(i + 1) * UPSAMPLE_FACTOR] = np.real(frame_downsampled[:UPSAMPLE_FACTOR])
        pass
    # nfft = next_power_of_2(len(left) * UPSAMPLE_FACTOR)
    # left_upsampled = upsample(left, UPSAMPLE_FACTOR)
    # left_ffted = scipy.fft.fft(left_upsampled, nfft)
    # lpf_ffted = scipy.fft.fft(lpf_coefficients, nfft)
    # result = left_ffted * lpf_ffted
    # frame_output = scipy.fft.ifft(result)
    # left_downsampled = downsample(frame_output, DOWNSAMPLE_FACTOR)
    return output


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
    