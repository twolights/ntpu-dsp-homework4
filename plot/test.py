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
    lpf_ffted = scipy.fft.fft(lpf_padded)
    # lpf_padded = np.pad(lpf_coefficients, (0, N - len(lpf_coefficients)))

    num_take = DOWNSAMPLE_FACTOR + ORDER - 1
    num_buffer_take = nfft - num_take
    temp_buffer = np.zeros(nfft, dtype=np.complex64)
    output_size = math.floor(DOWNSAMPLE_FACTOR / UPSAMPLE_FACTOR) * UPSAMPLE_FACTOR
    size = int(output_size / UPSAMPLE_FACTOR)

    for i in range(0, num_frames):
        frame = left[i * DOWNSAMPLE_FACTOR:(i + 1) * DOWNSAMPLE_FACTOR]
        frame_upsampled = upsample(frame, UPSAMPLE_FACTOR)
        frame_output = np.zeros_like(frame_upsampled)
        for j in range(0, UPSAMPLE_FACTOR):
            # chunk zero padding
            chunk = np.zeros(nfft, dtype=np.complex64)
            taken = frame_upsampled[j * DOWNSAMPLE_FACTOR:(j + 1) * DOWNSAMPLE_FACTOR]
            chunk_size = min(DOWNSAMPLE_FACTOR, taken.shape[0])
            chunk[:chunk_size] = taken
            chunk_ffted = scipy.fft.fft(chunk)
            chunk_lpfed = chunk_ffted * lpf_ffted
            chunk_iffted = scipy.fft.ifft(chunk_lpfed)
            chunk_taken = chunk_iffted[:num_take] + temp_buffer[:num_take]
            temp_buffer[:num_take] = 0
            np.roll(temp_buffer, -1 * num_take)
            temp_buffer[:num_buffer_take] += chunk_iffted[num_take:]
            if chunk_size < DOWNSAMPLE_FACTOR:
                frame_output[-1 * chunk_size] = np.real(chunk_taken[chunk_size])
            else:
                frame_output[j * DOWNSAMPLE_FACTOR:(j + 1) * DOWNSAMPLE_FACTOR] = np.real(chunk_taken[:DOWNSAMPLE_FACTOR])
            # frame_output[j * DOWNSAMPLE_FACTOR:(j + 1) * DOWNSAMPLE_FACTOR] = np.real(chunk_taken[:DOWNSAMPLE_FACTOR])
        downsampled = downsample(frame_output, DOWNSAMPLE_FACTOR)
        downsampled_size = downsampled.shape[0]
        if downsampled_size < UPSAMPLE_FACTOR:
            output[-1 * downsampled_size:] = downsampled
        else:
            output[i * UPSAMPLE_FACTOR:(i + 1) * UPSAMPLE_FACTOR] = downsampled
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
    