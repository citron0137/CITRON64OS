#	빌드 환경
NASM64 = nasm -f elf64
GCC64 = gcc -c -m64 -ffreestanding
LD64 = ld -melf_x86_64 -T ../elf_x86_64.x -nostdlib -e Main -Ttext 0x0200000
OBJCOPY64 = objcopy -j .text -j .data -j .rodata -j .bss -S -O binary

OBJDIRECTORY = Temp
SOURCEDIRECTORY = Source

#	빌드 항목 및 빌드 방법
all: prepare Kernel64.bin

prepare:
	mkdir -p $(OBJDIRECTORY)

dep:
	@echo ==== Make Dependancy File ====
	make -C $(OBJDIRECTORY) -f ../makefile InernalDependency
	@echo ==== Dependancy Search Complete ====

ExcuteInternalBuild: dep 
	make -C $(OBJDIRECTORY) -f ../makefile Kernel64.elf

Kernel64.bin: ExcuteInternalBuild 
	$(OBJCOPY64) $(OBJDIRECTORY)/Kernel64.elf $@

clean:
	rm -f *.bin
	rm -f $(OBJDIRECTORY)/*.*

#	make에 의해 다시 호출되는 부분 (Temp 디렉터리 기준)
ENTRYPOINTSOURCEFILE = ../$(SOURCEDIRECTORY)/EntryPoint.s 
ENTRYPOINTOBJECTFILE = EntryPoint.o

CSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.c)
ASSEMBLYSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.asm)
COBJECTFILES = $(notdir $(patsubst %.c,%.o,$(CSOURCEFILES)))
ASSEMBLYOBJECTFILES = $(notdir $(patsubst %.asm,%.o,$(ASSEMBLYSOURCEFILES)))

$(ENTRYPOINTOBJECTFILE): $(ENTRYPOINTSOURCEFILE)
	$(NASM64) -o $@ $<

%.o: ../$(SOURCEDIRECTORY)/%.c 
	$(GCC64) -c $<

%.o: ../$(SOURCEDIRECTORY)/%.asm
	$(NASM64) -o $@ $<

InernalDependency:
	$(GCC64) -MM $(CSOURCEFILES) > Dependancy.dep 

Kernel64.elf: $(ENTRYPOINTOBJECTFILE) $(COBJECTFILES) $(ASSEMBLYOBJECTFILES)
	$(LD64) -o $@ $^

ifeq (Dependancy.dep, $(wildcard Dependancy.dep))
include Dependancy.dep
endif