#!/usr/bin/python

import os
import re

kernels = []
lines = open('/boot/grub/grub.cfg').readlines()
for l in lines:
    m = re.search(r"'(Ubuntu, with Linux (\d+\.\d+\.\d+).*-generic)'", l)
    if m:
        kernels.append('Advanced options for Ubuntu>%s: %s' % (m.group(1), m.group(2)))


open('kernel.lst', 'w').write('\n'.join(kernels))