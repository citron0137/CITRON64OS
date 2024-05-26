all: BootLoader Kernel32 ImageMaker Disk.img

BootLoader:
	@echo
	@echo ============= Build Boot Loader =============
	@echo

	make -C 00.BootLoader
	
	@echo
	@echo ============= Build Complete =============
	@echo

Kernel32:
	@echo
	@echo ============= Build Kernel32 =============
	@echo

	make -C 01.Kernel32
	
	@echo
	@echo ============= Build Complete =============
	@echo


ImageMaker:
	@echo
	@echo ============= Build ImageMaker =============
	@echo

	make -C 04.Utility/00.ImageMaker
	cp 04.Utility/00.ImageMaker/ImageMaker .
	
	@echo
	@echo ============= Build Complete =============
	@echo


Disk.img: 00.BootLoader/BootLoader.bin 01.Kernel32/Kernel32.bin
	@echo
	@echo ============= Disk Image Build Start =============
	@echo

	./ImageMaker $^

	@echo
	@echo ============= Disk Image Build Complete =============
	@echo

clean:
	make -C 00.BootLoader clean
	make -C 01.Kernel32 clean
	make -C 04.Utility/00.ImageMaker clean
	rm -f ImageMaker
	rm -f Disk.img

