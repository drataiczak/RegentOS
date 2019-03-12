CC := $(TARGET)-gcc
AR := $(TARGET)-ar

INCLUDE := -Iinclude

CFLAGS := -Wall -Werror -Wextra -ffreestanding $(INCLUDE) -c
ARFLAGS := rcs


INCLDIR := ./include

SRC := $(wildcard *.c)
OBJS := $(patsubst %.c, $(BUILDDIR)/%.o, $(SRC))

.PHONY: all

all: $(OBJS)
	echo $(BUILDHDR)
	$(AR) $(ARFLAGS) $(BUILDLIB)/librn.a $(OBJS)
	cp $(INCLDIR)/* $(BUILDHDR)

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@
