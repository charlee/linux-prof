import os
import sys
import csv
import numpy as np
import matplotlib.pyplot as plt

def avg_file(filename):
    data = np.loadtxt(filename)
    label = os.path.basename(filename).replace('.csv', '').replace('test_', '')

    return (label, len(data), np.mean(data), np.std(data))

def avg_all(filenames, output_file):

    with open(output_file, 'w') as f:
        csvwriter = csv.writer(f)
        for filename in filenames:
            data = avg_file(filename)
            csvwriter.writerow(data)


if __name__ == '__main__':
    output = sys.argv[1]
    avg_all(sys.argv[2:], output)