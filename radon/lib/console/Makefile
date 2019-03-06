CC := $(TGT)-gcc

INCLUDE := -Iinclude

CFLAGS := -Wall -Werror -Wextra -ffreestanding $(INCLUDE) -c

BUILD := ../build

INCLDIR := ./include

SRC := $(wildcard *.c)
OBJS := $(patsubst %.c, $(BUILD)/%.o, $(SRC))

.PHONY: all clean

all: $(OBJS)
	
$(OBJS): $(SRC)
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD)
