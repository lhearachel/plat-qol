ifeq ($(strip $DEVKITPRO),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPro)
endif

ifeq ($(strip $DEVKITARM),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOOLCHAIN := $(DEVKITARM)

.PHONY: clean all

SYSTEM = $(shell grep -i -q 'microsoft' /proc/version; echo $$?)

ifeq ($(SYSTEM), 0)
EXE := .exe
SEP := \\

else
EXE := 
SEP := /

endif

default: all

ROMNAME = rom.nds
BUILDROM = test.nds
####################### Tools #########################
PYTHON = python3
NDSTOOL = tools/ndstool
ARMIPS = tools/armips
NARCHIVE = $(PYTHON) tools/narcpy.py
###################### Settings ########################
ARM_PREFIX = bin/arm-none-eabi-
AS = $(DEVKITARM)/$(ARM_PREFIX)as
CC = $(DEVKITARM)/$(ARM_PREFIX)gcc
LD = $(DEVKITARM)/$(ARM_PREFIX)ld
OBJCOPY = $(DEVKITARM)/$(ARM_PREFIX)objcopy

BUILDSYS := buildsys

LDFLAGS = $(BUILDSYS)/rom.ld -T $(BUILDSYS)/linker.ld
LDFLAGS_FIELD = $(BUILDSYS)/rom_gen.ld -T $(BUILDSYS)/linker_field.ld
LDFLAGS_BATTLE = $(BUILDSYS)/rom_gen.ld -T $(BUILDSYS)/linker_battle.ld
ASFLAGS = -mthumb -I ./data
CFLAGS = -I ./include -mthumb -mno-thumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi -mno-long-calls -march=armv4t -Wall -Wextra -Os -fira-loop-pressure -fipa-pta

LINK = build/linked.o
OUTPUT = build/output.bin
BATTLE_LINK = build/battle_linked.o
BATTLE_OUTPUT = build/output_battle.bin
FIELD_LINK = build/field_linked.o
FIELD_OUTPUT = build/output_field.bin
####################### output ########################
C_SUBDIR = src
ASM_SUBDIR = asm
INCLUDE_SUBDIR = include
BUILD := build
BUILD_NARC := $(BUILD)/narc
BASE := base
FILESYS := $(BASE)/data

INCLUDE_SRCS := $(wildcard $(INCLUDE_SUBDIR)/*.h)

C_SRCS := $(wildcard $(C_SUBDIR)/*.c)
C_OBJS := $(patsubst $(C_SUBDIR)/%.c,$(BUILD)/%.o,$(C_SRCS))

ASM_SRCS := $(wildcard $(ASM_SUBDIR)/*.s)
ASM_OBJS := $(patsubst $(ASM_SUBDIR)/%.s,$(BUILD)/%.d,$(ASM_SRCS))
OBJS     := $(C_OBJS) $(ASM_OBJS)

####################### Build #########################
rom_gen.ld:$(LINK) $(OUTPUT) $(BUILDSYS)/rom.ld
	cp $(BUILDSYS)/rom.ld $(BUILDSYS)/rom_gen.ld
	$(PYTHON) scripts/generate_ld.py

$(BUILD)/%.d:asm/%.s
	$(AS) $(ASFLAGS) -c $< -o $@

$(BUILD)/%.o:src/%.c
	mkdir -p $(BUILD)
	@echo -e "Compiling"
	$(CC) $(CFLAGS) -c $< -o $@

$(LINK):$(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(OUTPUT):$(LINK)
	$(OBJCOPY) -O binary $< $@


generate_output:$(OUTPUT)
	$(PYTHON) scripts/generate_ld.py


all: generate_output
	rm -rf $(BASE)
	mkdir -p $(BASE)
	mkdir -p $(BUILD)

	$(NDSTOOL) -x $(ROMNAME) -9 $(BASE)/arm9.bin -7 $(BASE)/arm7.bin -y9 $(BASE)/y9.bin -y $(BASE)/y7.bin -d $(FILESYS) -y $(BASE)/overlay -t $(BASE)/banner.bin -h $(BASE)/header.bin
	@echo " === ROM decompression successful! === "
	@echo " ==== Starting code injection... ===== "

	$(PYTHON) scripts/make.py
	# $(ARMIPS) armips/global.s
	
	@echo " =========== Making ROM... =========== "
	$(NDSTOOL) -c $(BUILDROM) -9 $(BASE)/arm9.bin -7 $(BASE)/arm7.bin -y9 $(BASE)/y9.bin -y $(BASE)/y7.bin -d $(FILESYS) -y $(BASE)/overlay -t $(BASE)/banner.bin -h $(BASE)/header.bin
	@echo " =============== Done! =============== "


build_tools:
	mkdir -p tools/source

	rm -r -f tools/source/ndstool
	cd tools/source ; git clone https://github.com/devkitPro/ndstool.git
	cd tools/source/ndstool ; git checkout fa6b6d01881363eb2cd6e31d794f51440791f336
	cd tools/source/ndstool ; find . -name '*.sh' -execdir chmod +x {} \;
	cd tools/source/ndstool ; ./autogen.sh
	cd tools/source/ndstool ; ./configure && $(MAKE)
	mv tools/source/ndstool/ndstool tools/ndstool

	rm -r -f tools/source/armips
	cd tools/source ; git clone --recursive https://github.com/Kingcom/armips.git
	cd tools/source/armips ; mkdir build
	cd tools/source/armips/build ; cmake -DCMAKE_BUILD_TYPE=Release ..
	cd tools/source/armips/build ; cmake --build .
	mv tools/source/armips/build/armips tools/armips

	rm -r -f tools/source


tidy:
	rm -rf $(BUILD)
	rm -rf $(BASE)


clean_tools:
	rm -f tools/ndstool
	rm -f tools/armips
	rm -f tools/source


clean: tidy clean_tools
