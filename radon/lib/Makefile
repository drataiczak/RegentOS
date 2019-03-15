INCLUDE := -Iinclude

CFLAGS := -Wall -Werror -Wextra -ffreestanding $(INCLUDE) -c
ARFLAGS := rcs

INCLDIR := ./include

SRC := $(wildcard *.c)
OBJS := $(patsubst %.c, $(BUILDLIB)/%.o, $(SRC))

all: $(OBJS)
	$(AR) $(ARFLAGS) $(BUILDLIB)/librn.a $(OBJS)
	cp $(INCLDIR)/* $(BUILDHDR)

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@
