#!/bin/bash

make clean
make 

mkdir -p logs
rm -rf logs/*

qemu-system-x86_64 \
    -no-reboot -no-shutdown \
    -L . -m 64m \
    -fda ./CITRON64/Disk.img \
    -M pc \
    -d int,cpu_reset,guest_errors,page \
    -D logs/qemu_debug.log \
    -vga std \
    -serial file:logs/serial.log \
    -monitor stdio
