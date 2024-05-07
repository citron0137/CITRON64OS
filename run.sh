#!/bin/bash

make -C CITRON64 clean
make -C CITRON64
qemu-system-x86_64 -L . -m 64 -fda ./CITRON64/Disk.img -M pc