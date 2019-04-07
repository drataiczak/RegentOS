ARCHLIB := $(ROOTDIR)/radon/arch/$(ARCH)/lib
ARCHLIBHDR := $(ARCHLIB)/include

INCLDIR := ./include
INCLUDE := -I$(INCLDIR) -I$(ARCHLIBHDR)

CFLAGS := -Wall -Werror -Wextra -ffreestanding $(INCLUDE) -g
ARFLAGS := rcs

AS := nasm
ASFLAGS := -felf32

# The asm is arch dependent and the basis of the C
AS_SRC := $(wildcard $(ARCHLIB)/*.asm)
AS_OBJS := $(patsubst $(ARCHLIB)/%.asm, $(BUILDLIB)/%.o, $(AS_SRC))

SRC :=  $(wildcard *.c)
OBJS := $(patsubst %.c, $(BUILDLIB)/%.o, $(SRC))

all: $(AS_OBJS) $(OBJS)
	$(AR) $(ARFLAGS) $(BUILDLIB)/librn.a $(OBJS) $(AS_OBJS)
	cp $(INCLDIR)/* $(BUILDHDR)

$(BUILDLIB)/%.o: $(ARCHLIB)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDLIB)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

