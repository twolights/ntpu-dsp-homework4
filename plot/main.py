import os.path

import numpy as np
import scipy

SOURCE_SAMPLING_RATE = 44100
TARGET_SAMPLING_RATE = 8000

UPSAMPLE_FACTOR = 80
DOWNSAMPLE_FACTOR = 441


def upsample(data: np.ndarray, factor: int) -> np.ndarray:
    shape = data.shape
    num_samples, num_channels = shape
    total = num_channels * num_samples
    z = np.zeros(total * factor)
    z[::factor] = data.reshape(total)
    return z.reshape((num_samples * factor, num_channels))


def main():
    file_name = os.path.join(os.path.dirname(__file__), '..', 'input', 'up-is-down.wav')
    sr, data = scipy.io.wavfile.read(file_name)
    length = data.shape[0] / sr
    data = upsample(data, UPSAMPLE_FACTOR)
    r = np.random.random()


if __name__ == '__main__':
    main()
