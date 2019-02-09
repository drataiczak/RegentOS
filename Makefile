BUILDDIR := ./build
HEDIR := ./helium
TOOLDIR := ./tool

LAYER ?= helium

.PHONY: all helium run
all: $(BUILDDIR) helium

$(BUILDDIR):
	mkdir ./build

helium:
	make -C $(HEDIR)

run: $(LAYER)
	qemu-system-i386 -kernel $(BUILDDIR)/$(LAYER).bin

clean:
	rm -rf $(BUILDDIR)/*

