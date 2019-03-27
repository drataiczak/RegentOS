INCLDIR := ./include
INCLUDE := -I$(INCLDIR)

CFLAGS := -Wall -Werror -Wextra -ffreestanding $(INCLUDE) -g
ARFLAGS := rcs

SRC :=  $(wildcard *.c)
OBJS := $(patsubst %.c, $(BUILDLIB)/%.o, $(SRC))

all: $(OBJS)
	$(AR) $(ARFLAGS) $(BUILDLIB)/librn.a $(OBJS)
	cp $(INCLDIR)/* $(BUILDHDR)

$(BUILDLIB)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

