import os
import sys
import csv

def avg_file(filename):
    lines = open(filename).readlines()
    nums = [int(line) for line in lines]

    label = os.path.basename(filename).replace('.csv', '').replace('test_', '')
    total = sum(nums)
    count = len(nums)
    if count == 0:
        avg = 0
    else:
        avg = int(total / count)

    return (label, total, count, avg)

def avg_all(filenames, output_file):

    with open(output_file, 'w') as f:
        csvwriter = csv.writer(f)
        for filename in filenames:
            data = avg_file(filename)
            csvwriter.writerow(data)


if __name__ == '__main__':
    output = sys.argv[1]
    avg_all(sys.argv[2:], output)