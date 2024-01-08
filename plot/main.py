import os

import matplotlib.pyplot as plt
import numpy as np


def main():
    input_file = os.path.join(os.path.dirname(__file__), '..', 'output', 'lpf.csv')
    output_file = os.path.join(os.path.dirname(__file__), '..', 'output', 'ir-and-magnitude.png')

    fig, (ir, mag) = plt.subplots(2)
    fig.tight_layout()
    fig.set_figwidth(8)
    fig.set_figheight(10)

    data = np.loadtxt(input_file, dtype='float64')
    x = np.arange(0, data.shape[0])
    ir.set_title('Impulse Response')
    ir.plot(x, data)

    X = np.fft.fft(data)
    freq = np.fft.fftfreq(data.shape[0])
    mag.set_title('Magnitude')
    mag.plot(freq, np.abs(X))
    plt.savefig(output_file)


if __name__ == '__main__':
    main()
