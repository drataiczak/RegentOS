CC := $(TARGET)-gcc
AS := nasm
LD := $(CC)
QEMU := qemu-system-i386

# The default architecture as of now... figure out how to make this variable
ARCH := x86

ARCHDIR := ./arch/$(ARCH)
KNLDIR := ./kernel
BUILD_DIR := ../build
ISODIR := $(BUILD_DIR)/isodir/
LIBDIR := ./lib
LIBKDIR := $(LIBDIR)/build
LIBKHDR := $(wildcard $(LIBDIR)/*/include)

CFLAGS := -ffreestanding -nostdlib -Wall -Werror -Wextra -I$(LIBKHDR)
ASFLAGS := -felf32
LDFLAGS := -nostdlib -ffreestanding -L$(LIBKDIR)
QEMUFLAGS := -cdrom

ARTOOLS := ../boot

LIBK := -L$(LIBKDIR)
CLIBS := -lgcc
LDLIBS := -lk

LD_FILES := $(ARTOOLS)/linker.ld
GRUB_CFG := $(ARTOOLS)/grub.cfg

AS_FILES := $(wildcard $(ARCHDIR)/*.asm)
AS_OBJS := $(patsubst $(ARCHDIR)/%.asm, $(BUILD_DIR)/%.o, $(AS_FILES))

C_FILES := $(wildcard $(KNLDIR)/*.c)
C_OBJS := $(patsubst $(KNLDIR)/%.c, $(BUILD_DIR)/%.o, $(C_FILES))

BIN := $(BUILD_DIR)/radon.bin
ISO := $(BUILD_DIR)/RegentOS.iso

.PHONY: all run clean

all: $(AS_OBJS) $(C_OBJS) libk
	$(LD) -T $(LD_FILES) -o $(BIN) $(LDFLAGS) $(wildcard $(BUILD_DIR)/*.o) $(LDLIBS)
	mkdir -p $(ISODIR)/boot/grub
	cp $(BIN) $(ISODIR)/boot
	cp $(GRUB_CFG) $(ISODIR)/boot/grub
	grub-mkrescue -o $(ISO) $(ISODIR)

$(AS_OBJS): $(AS_FILES)
	$(AS) $(ASFLAGS) $< -o $@

$(C_OBJS): $(C_FILES)
	$(CC) $(CFLAGS) -c $^ -o $@ $(CLIBS)

libk:
	make -C $(LIBDIR) 

run:
	$(QEMU) $(QEMUFLAGS) $(ISO)

clean:
	rm -rf $(BUILD_DIR)/*
	make -C $(LIBDIR) clean
