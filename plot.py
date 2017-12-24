import os
import sys
import numpy as np
import matplotlib.pyplot as plt

def reject_outliers(data, m=2):
    return data[abs(data - np.mean(data)) < m * np.std(data)]

def plot_file(filename, output):
    data = np.loadtxt(filename)
    data = reject_outliers(data)
    plt.figure()
    plt.plot(data)
    plt.ylabel('Cycles')
    plt.suptitle(label)
    plt.savefig(output)
    plt.close()


if __name__ == '__main__':
    filename = sys.argv[1]
    label = os.path.basename(filename).replace('.csv', '').replace('test_', '')
    output = 'plot/{}.png'.format(label)
    plot_file(filename, output)
