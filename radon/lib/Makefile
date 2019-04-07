INCLDIR := ./include
INCLUDE := -I$(INCLDIR)

CFLAGS := -Wall -Werror -Wextra -ffreestanding $(INCLUDE) -g
ARFLAGS := rcs

AS := nasm
ASFLAGS := -felf32

AS_SRC := $(wildcard *.asm)
AS_OBJS := $(patsubst %.asm, $(BUILDLIB)/%.o, $(AS_SRC))

SRC :=  $(wildcard *.c)
OBJS := $(patsubst %.c, $(BUILDLIB)/%.o, $(SRC))

all: $(AS_OBJS) $(OBJS)
	$(AR) $(ARFLAGS) $(BUILDLIB)/librn.a $(OBJS) $(AS_OBJS)
	cp $(INCLDIR)/* $(BUILDHDR)

$(BUILDLIB)/%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDLIB)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

