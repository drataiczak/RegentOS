CC := $(TARGET)-gcc
AS := nasm
AR := $(TARGET)-ar
LD := $(CC)

BUILDDIR := $(shell pwd)/build
BUILDHDR := $(BUILDDIR)/include
BUILDBIN := $(BUILDDIR)/bin
BUILDKNL := $(BUILDDIR)/kernel
BUILDLIB := $(BUILDDIR)/lib
BUILDISO := $(BUILDDIR)/isodir
BUILDBOOT := ./boot

ARCH := x86

RNDIR := ./radon

TOOLDIR := ./tool

LAYER ?= radon

BIN := RegentOS

QEMU := qemu-system-i386

QEMUFLAGS := -cdrom $(BUILDBIN)/$(BIN).iso

export CC
export AS
export AR
export LD
export BUILDDIR
export BUILDHDR
export BUILDBIN
export BUILDKNL
export BUILDLIB
export BUILDISO
export BUILDBOOT
export ARCH

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

