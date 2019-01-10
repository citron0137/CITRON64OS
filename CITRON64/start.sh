#!/bin/sh

qemu-system-x86_64 -L . -m 256 -fda Disk.img -localtime -M pc -s -S
