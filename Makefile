BUILDDIR := ./build
RNDIR := ./radon
TOOLDIR := ./tool

LAYER ?= helium

.PHONY: all radon run
all: $(BUILDDIR) radon

$(BUILDDIR):
	mkdir ./build

radon:
	make -C $(RNDIR)

run: $(LAYER)
	qemu-system-i386 -kernel $(BUILDDIR)/$(LAYER).bin

clean:
	rm -rf $(BUILDDIR)/*

