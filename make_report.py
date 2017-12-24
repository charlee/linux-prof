"""
Generate reports with actual benchmark data.
The data should be a single ".tar" file which contains output.tar.gz for each kernel version.

all.tar
  |- output-4.4.0.tar.gz
  |- output-4.3.0.tar.gz
  |- output-4.2.0.tar.gz
  |- ....

`report/report.csv` will be generated to summarize the data for all the kernel versions.
For each system call, a bar graph will be generated under `report` directory as well.


Usage:
    python make_reports.py <datafile.tar>

"""

import os
import sys
import csv
import numpy as np
import matplotlib.pyplot as plt


def reject_outliers(data, m=2):
    return data[abs(data - np.mean(data)) < m * np.std(data)]

def avg_file(filename):
    data = np.loadtxt(filename)
    data = reject_outliers(data)
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