"""
Generate reports with actual benchmark data.
The data should be a single ".tar" file which contains output.tar.gz for each kernel version.

all.tar
  |- output-4.4.0.tar.gz
  |- output-4.3.0.tar.gz
  |- output-4.2.0.tar.gz
  |- ....

`report/means.csv` and `report/stds.csv` will be generated to summarize the data for all the kernel versions.
For each system call, a bar graph will be generated under `report` directory as well.


Usage:
    python make_reports.py <datafile.tar>

"""

import os
import re
import sys
import csv
import tarfile
import pickle
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict


def reject_outliers(data, m=2):
    return data[abs(data - np.mean(data)) < m * np.std(data)]


def process_syscall_csv(fd):
    data = np.loadtxt(fd, dtype=np.uint32)
    data = reject_outliers(data)
    return np.mean(data), np.std(data)


def process_single(fd):
    """Process a single tar.gz file.

    Output:
        labels: 1D array of syscall names.
        means: 1D array of averages.
        stds: 1D array of stds.
    """

    datatar = tarfile.open(fileobj=fd, mode='r')

    labels = []
    means = []
    stds = []

    info = datatar.next()
    while info is not None:
        if info.isfile() and info.name.endswith('.csv'):
            print('  - Found csv file %s, processing...' % info.name)
            m = re.search(r'output/(.*)\.csv', info.name)
            if m:
                syscall_name = m.group(1)
                f = datatar.extractfile(info)
                mean, std = process_syscall_csv(f)
                f.close()

                labels.append(syscall_name)
                means.append(mean)
                stds.append(std)

        info = datatar.next()

    return labels, means, stds

def process_all(data_fd):
    """Procsess a data.tar file.

    Output:
        means: 2D array with shape of (syscalls, kernel_versions).
        stdk: 2D array with shape of (syscalls, kernel_versions).
    """

    kernel_versions = []
    all_means = defaultdict(list)
    all_stds = defaultdict(list)

    alltar = tarfile.open(fileobj=data_fd, mode='r')
    info = alltar.next()

    while info is not None:
        if info.isfile() and info.name.endswith('.tar.gz'):
            print('Found data file %s, processing...' % info.name)

            m = re.search(r'.*output-(\d+\.\d+\.\d+)\.tar\.gz.*', info.name)
            if m:
                kernel_version = m.group(1)
                f = alltar.extractfile(info)
                labels, means, stds = process_single(f)

                kernel_versions.append(kernel_version)
                for idx, label in enumerate(labels):
                    all_means[label].append(means[idx])
                    all_stds[label].append(stds[idx])

                f.close()

        info = alltar.next()


    # sort syscall labels
    all_labels = sorted(all_means.keys(), key=lambda k: int(k[:2], 16))
    
    # Convert kernel versions to number for sorting
    def numeric_version(version_str):
        parts = version_str.split('.')
        return int(parts[0]) * 1000000 + int(parts[1]) * 1000 + int(parts[2])

    version_numbers = [numeric_version(v) for v in kernel_versions]
    version_idx = np.argsort(version_numbers)
    all_kernel_versions = [kernel_versions[i] for i in version_idx]

    # Convert to nparray
    means_mat = np.array([all_means[label] for label in all_labels])[:,version_idx]
    stds_mat = np.array([all_stds[label] for label in all_labels])[:,version_idx]

    return means_mat, stds_mat, all_labels, all_kernel_versions


def plot(filename, means, stds, versions, label):
    versions = ['.'.join(v.split('.')[:2]) for v in versions]
    idx = np.arange(means.shape[0])
    fig, ax = plt.subplots()
    ax.bar(idx, means, yerr=stds)
    ax.set_title(label)
    ax.set_ylabel('Cycles')
    ax.set_xticks(idx)
    lbls = ax.set_xticklabels(versions)
    plt.setp(lbls, rotation=90)
    plt.savefig(filename)
    plt.close()

def save_csv(filename, mat, labels, versions):
    with open(filename, 'w') as csvfile:
        writer = csv.writer(csvfile, delimiter=',')
        writer.writerow(['syscall']+versions)
        for i, row in enumerate(mat):
            writer.writerow([labels[i]] + list(row))


if __name__ == '__main__':
    datatar = sys.argv[1]
    with open(datatar, 'r') as fd:
        means_mat, stds_mat, all_labels, all_kernel_versions = process_all(fd)
        means_mat = means_mat.astype(np.uint32)
        stds_mat = stds_mat.astype(np.uint32)
        for idx, label in enumerate(all_labels):
            plot('report/%s.png' % label, means_mat[idx], stds_mat[idx], all_kernel_versions, label)
        save_csv('report/means.csv', means_mat, all_labels, all_kernel_versions)
        save_csv('report/stds.csv', stds_mat, all_labels, all_kernel_versions)
