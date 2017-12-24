#!/usr/bin/python

import os

BASEDIR = os.path.dirname(__file__)

grub_pos_file = os.path.join(BASEDIR, 'kernel-grub-pos.tmp')
kernel_version_file = os.path.join(BASEDIR, 'kernel-version.tmp')
kernel_list = os.path.join(BASEDIR, 'kernel.lst')

if not os.path.isfile(grub_pos_file):
    grub_pos = 0
else:
    line = open(grub_pos_file).read()
    grub_pos = int(line)


# Read kernel list and grub menu position
lines = open(kernel_list).readlines()
kernels = []
for l in lines:
    l = l.strip()
    if not l:
        continue
    grub, version = l.split(',')
    grub = grub.strip()
    version = version.strip()
    kernels.append([grub, version])


if len(kernels) <= grub_pos:
    print("Done.")
    exit(1)
else:
    kernel = kernels[grub_pos]
    open(kernel_version_file, 'w').write(kernel[1])
    open(grub_pos_file, 'w').write('%s' % (grub_pos+1))
    print('grub-set-default "%s"' % kernel[0])
    os.system('grub-set-default "%s"' % kernel[0])
    os.system('shutdown -r now')
    exit(0)
