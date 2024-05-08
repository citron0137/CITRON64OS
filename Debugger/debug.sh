#!/bin/bash

make -C ../CITRON64 clean
make -C ../CITRON64

qemu-system-i386 -L . -m 64 -fda ../CITRON64/Disk.img -M pc -s -S &

sleep 1s

gdb -q \
	-ix "gdb_init_real_mode.txt" \
	-ex "target remote :1234" \
	-ex "b *0x7c00" \
	-ex "c" 
	
	# -ex "set tdesc filename target.xml" \