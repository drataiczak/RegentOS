CC := $(TARGET)-gcc
AR := $(TARGET)-ar

INCLUDE := -Iinclude

CFLAGS := -Wall -Werror -Wextra -ffreestanding $(INCLUDE) -c
ARFLAGS := rcs

BUILD := ../build

INCLDIR := ./include

SRC := $(wildcard *.c)
OBJS := $(patsubst %.c, $(BUILD)/%.o, $(SRC))

.PHONY: all clean

all: $(OBJS)
	$(AR) $(ARFLAGS) $(BUILD)/libk.a $(OBJS)
	
$(OBJS): $(SRC)
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@
