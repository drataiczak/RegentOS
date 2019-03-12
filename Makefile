BUILDDIR := $(shell pwd)/build
BUILDHDR := $(BUILDDIR)/include
BUILDBIN := $(BUILDDIR)/bin
BUILDKNL := $(BUILDDIR)/kernel
BUILDLIB := $(BUILDDIR)/lib
BUILDISO := $(BUILDDIR)/isodir

RNDIR := ./radon

TOOLDIR := ./tool

LAYER ?= radon

BIN := RegentOS

QEMU := qemu-system-i386

QEMUFLAGS := -cdrom $(BUILDBIN)/$(BIN).iso

export BUILDDIR
export BUILDHDR
export BUILDBIN
export BUILDKNL
export BUILDLIB
export BUILDISO

.PHONY: all radon run

all: radon

radon: buildenv
	make -C $(LAYER)

buildenv:
	mkdir -p $(BUILDDIR) $(BUILDHDR) $(BUILDBIN) $(BUILDKNL) $(BUILDLIB) $(BUILDISO)/boot/grub

run: $(LAYER)
	$(QEMU) $(QEMUFLAGS)

clean:
	rm -rf $(BUILDDIR)

