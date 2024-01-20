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

    nfft = 2048
    # nfft = next_power_of_2(DOWNSAMPLE_FACTOR * UPSAMPLE_FACTOR)
    lpf_coefficients = scipy.signal.firwin(ORDER, CUTOFF, window='hamming', fs=FS * UPSAMPLE_FACTOR)
    lpf_padded = np.pad(lpf_coefficients, (0, nfft - len(lpf_coefficients)))
    lpf_padded_ffted = scipy.fft.fft(lpf_padded)
    # lpf_padded = np.pad(lpf_coefficients, (0, N - len(lpf_coefficients)))

    temp_buffer = np.zeros(nfft, dtype=np.complex64)
    segment_buffer = np.zeros(nfft, dtype=np.complex64)
    output_size = math.floor(DOWNSAMPLE_FACTOR / UPSAMPLE_FACTOR) * UPSAMPLE_FACTOR
    size = int(output_size / UPSAMPLE_FACTOR)

    for i in range(0, num_frames):
        frame = left[i * DOWNSAMPLE_FACTOR:(i + 1) * DOWNSAMPLE_FACTOR]
        frame_upsampled = upsample(frame, UPSAMPLE_FACTOR)
        for j in range(0, UPSAMPLE_FACTOR):
            if (i * UPSAMPLE_FACTOR + j) > len(output):
                break
            chunk = frame_upsampled[j * DOWNSAMPLE_FACTOR:(j + 1) * DOWNSAMPLE_FACTOR]
            if len(chunk) < DOWNSAMPLE_FACTOR:
                chunk = np.pad(chunk, (0, DOWNSAMPLE_FACTOR - len(chunk)))
            segment_buffer[:DOWNSAMPLE_FACTOR] = chunk
            # Already padded
            segment_ffted = scipy.fft.fft(segment_buffer)
            result = segment_ffted * lpf_padded_ffted
            segment_output = scipy.fft.ifft(result)
            segment_output[:output_size] += temp_buffer[:output_size]
            np.roll(temp_buffer, -1 * output_size)
            extra_size = (nfft - output_size)
            temp_buffer[:extra_size] += segment_output[output_size:]
            segment_downsampled = downsample(segment_output, DOWNSAMPLE_FACTOR)
            index = i * size + j
            if ((index + 1) * size) > len(output):
                output[index * size:] = np.real(segment_downsampled[:len(output) - index * size + index])
            else:
                output[index * size:(index + 1) * size] = np.real(segment_downsampled)
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
    