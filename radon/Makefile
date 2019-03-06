CC := $(TARGET)-gcc
AS := nasm
LD := $(CC)
QEMU := qemu-system-i386

# The default architecture as of now... figure out how to make this variable
ARCH := x86

CFLAGS := -ffreestanding -nostdlib -Wall -Werror -Wextra
ASFLAGS := -felf32
LDFLAGS := -nostdlib -ffreestanding
QEMUFLAGS := -cdrom

ARCHDIR := ./arch/$(ARCH)
KNLDIR := ./kernel
BUILD_DIR := ../build
ISODIR := $(BUILD_DIR)/isodir/

ARTOOLS := ../boot

CLIBS := -lgcc

LD_FILES := $(ARTOOLS)/linker.ld
GRUB_CFG := $(ARTOOLS)/grub.cfg

AS_FILES := $(wildcard $(ARCHDIR)/*.asm)
AS_OBJS := $(patsubst $(ARCHDIR)/%.asm, $(BUILD_DIR)/%.o, $(AS_FILES))

C_FILES := $(wildcard $(KNLDIR)/*.c)
C_OBJS := $(patsubst $(KNLDIR)/%.c, $(BUILD_DIR)/%.o, $(C_FILES))

BIN := $(BUILD_DIR)/radon.bin
ISO := $(BUILD_DIR)/RegentOS.iso

.PHONY: all run clean

all: $(AS_OBJS) $(C_OBJS)
	$(LD) -T $(LD_FILES) -o $(BIN) $(LDFLAGS) $(CRTI) $(CRTBEGIN) $(wildcard $(BUILD_DIR)/*.o) $(CRTEND) $(CRTN)
	mkdir -p $(ISODIR)/boot/grub
	cp $(BIN) $(ISODIR)/boot
	cp $(GRUB_CFG) $(ISODIR)/boot/grub
	grub-mkrescue -o $(ISO) $(ISODIR)

$(AS_OBJS): $(AS_FILES)
	$(AS) $(ASFLAGS) $< -o $@

$(C_OBJS): $(C_FILES)
	$(CC) $(CFLAGS) -c $^ -o $@ $(CLIBS)

run:
	$(QEMU) $(QEMUFLAGS) $(ISO)

clean:
	rm -rf $(BUILD_DIR)/*
