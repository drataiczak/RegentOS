ARCHDIR := ./arch/$(ARCH)
KNLDIR := ./kernel
LIBDIR := ./lib

CFLAGS := -ffreestanding -nostdlib -Wall -Werror -Wextra -I$(BUILDHDR)
ASFLAGS := -felf32
LDFLAGS := -nostdlib -ffreestanding -L$(BUILDLIB)

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

# Putting libk first to ensure headers are installed might be hacky and non-portable
all: libk $(AS_OBJS) $(C_OBJS)
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
