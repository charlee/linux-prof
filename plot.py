import os
import sys
import numpy as np
import matplotlib.pyplot as plt


def plot_file(filename, output):
    data = np.loadtxt(filename)
    plt.figure()
    plt.plot(data)
    plt.ylabel('Cycles')
    plt.suptitle(label)
    plt.savefig(output)
    plt.close()


if __name__ == '__main__':
    filename = sys.argv[1]
    label = os.path.basename(filename).replace('.csv', '').replace('test_', '')
    output = 'report/{}.png'.format(label)
    plot_file(filename, output)
