#!/bin/bash

make clean
make 
qemu-system-x86_64 -L . -m 64m -fda ./CITRON64/Disk.img -M pc
