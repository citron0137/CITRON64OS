#	빌드 환경
NASM32 = nasm
GCC32 = gcc -c -m32 -ffreestanding
LD32 = ld -melf_i386 -T ../elf_i386.x -nostdlib -e Main -Ttext 0x0200
OBJCOPY32 = objcopy -j .text -j .data -j .rodata -j .bss -S -O binary

OBJDIRECTORY = Temp
SOURCEDIRECTORY = Source

#	빌드 항목 및 빌드 방법
all: prepare Kernel32.bin

prepare:
	mkdir -p $(OBJDIRECTORY)

$(OBJDIRECTORY)/EntryPoint.bin: $(SOURCEDIRECTORY)/EntryPoint.s
	$(NASM32) -o $@ $<

dep:
	@echo ==== Make Dependancy File ====
	make -C $(OBJDIRECTORY) -f ../makefile InernalDependency
	@echo ==== Dependancy Search Complete ====

ExcuteInternalBuild: dep 
	make -C $(OBJDIRECTORY) -f ../makefile Kernel32.elf

$(OBJDIRECTORY)/Kernel32.elf.bin: ExcuteInternalBuild
	$(OBJCOPY32) $(OBJDIRECTORY)/Kernel32.elf $@

Kernel32.bin: $(OBJDIRECTORY)/EntryPoint.bin $(OBJDIRECTORY)/Kernel32.elf.bin 
	cat $^ > $@

clean:
	rm -f *.bin
	rm -f $(OBJDIRECTORY)/*.*

#	make에 의해 다시 호출되는 부분
CENTRYPOINTOBJECTFILE = Main.o
CSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.c)
ASSEMBLYSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.asm)
COBJECTFILES = $(subst Main.o, , $(notdir $(patsubst %.c,%.o,$(CSOURCEFILES))))
ASSEMBLYOBJECTFILES = $(notdir $(patsubst %.asm,%.o,$(ASSEMBLYSOURCEFILES)))

%.o: ../$(SOURCEDIRECTORY)/%.c 
	$(GCC32) -c $<

%.o: ../$(SOURCEDIRECTORY)/%.asm
	$(NASM32) -f elf32 -o $@ $<

InernalDependency:
	$(GCC32) -MM $(CSOURCEFILES) > Dependancy.dep 

Kernel32.elf: $(CENTRYPOINTOBJECTFILE) $(COBJECTFILES) $(ASSEMBLYOBJECTFILES)
	$(LD32) -o $@ $^

ifeq (Dependancy.dep, $(wildcard Dependancy.dep))
include Dependancy.dep
endif