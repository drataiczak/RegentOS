PROJ := helium

CC := $(TARGET)-gcc
AS := $(TARGET)-as
LD := $(TARGET)-ld
OC := $(TARGET)-objcopy

ASM_SRC := init.s
C_SRC := he_main.c
LD_SRC := linker.ld

BUILDDIR := ../build

ASM_OBJ = $(patsubst %.s, $(BUILDDIR)/%.o, $(ASM_SRC))
C_OBJ = $(patsubst %.c, $(BUILDDIR)/%.o, $(C_SRC))

ASMFLAGS := -g
CFLAGS := -g
OCFLAGS := -O binary

ELF := $(PROJ).elf
BIN := $(PROJ).bin

.PHONY: all

all: $(C_OBJ) $(ASM_OBJ)
	cp $(LD_SRC) $(BUILDDIR)
	cd $(BUILDDIR) && $(LD) -T $(LD_SRC) $(patsubst %.s, %.o, $(ASM_SRC)) $(patsubst %.c, %.o, $(C_SRC)) -o $(ELF)
	$(OC) $(OCFLAGS) $(BUILDDIR)/$(ELF) $(BUILDDIR)/$(BIN)
	cd -

$(ASM_OBJ): $(ASM_SRC)
	$(AS) $(ASMFLAGS) $< -o $@ 

$(C_OBJ): $(C_SRC)
	$(CC) $(CFLAGS) -c $< -o $@
