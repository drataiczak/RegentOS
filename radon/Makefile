CC := $(TARGET)-gcc
AS := nasm
LD := $(CC)

ARCHDIR := ./arch/$(ARCH)
KNLDIR := ./kernel
LIBDIR := ./lib
LIBKDIR := $(LIBDIR)/build
LIBKHDR := $(wildcard $(LIBDIR)/*/include)

CFLAGS := -ffreestanding -nostdlib -Wall -Werror -Wextra -I$(LIBKHDR)
ASFLAGS := -felf32
LDFLAGS := -nostdlib -ffreestanding -L$(LIBKDIR)

ARTOOLS := ../boot

LIBK := -L$(LIBKDIR)
CLIBS := -lgcc
LDLIBS := -lrn

LD_FILES := $(ARTOOLS)/linker.ld
GRUB_CFG := $(ARTOOLS)/grub.cfg

AS_FILES := $(wildcard $(ARCHDIR)/*.asm)
AS_OBJS := $(patsubst $(ARCHDIR)/%.asm, $(BUILDDIR)/%.o, $(AS_FILES))

C_FILES := $(wildcard $(KNLDIR)/*.c)
C_OBJS := $(patsubst $(KNLDIR)/%.c, $(BUILDDIR)/%.o, $(C_FILES))

BIN := $(BUILDBIN)/RegentOS.bin
ISO := $(BUILDBIN)/RegentOS.iso

.PHONY: all

all: $(AS_OBJS) $(C_OBJS) libk
	$(LD) -T $(LD_FILES) -o $(BIN) $(LDFLAGS) $(wildcard $(BUILDDIR)/*.o) $(LDLIBS)
	cp $(BIN) $(BUILDISO)/boot
	cp $(GRUB_CFG) $(BUILDISO)/boot/grub
	grub-mkrescue -o $(ISO) $(BUILDISO)

$(AS_OBJS): $(AS_FILES)
	$(AS) $(ASFLAGS) $< -o $@

$(C_OBJS): $(C_FILES)
	$(CC) $(CFLAGS) -c $^ -o $@ $(CLIBS)

libk:
	make -C $(LIBDIR) 
