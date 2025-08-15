#!/bin/bash

make -C ../CITRON64 clean
make -C ../CITRON64

qemu-system-i386 \
	-no-reboot -no-shutdown \
	-L . -m 64 \
	-fda ../CITRON64/Disk.img \
	-M pc \
	-s \
	-S &

sleep 1s

gdb -q \
	-ex "target remote :1234" \
	-ex "set disassembly-flavor intel" \
	-ex "layout asm" \
	-ex "layout reg" \
	-ex "b *0x10200" \
	-ex "c" 
	
	# -ex "set tdesc filename target.xml" \