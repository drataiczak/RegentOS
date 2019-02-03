BUILDDIR := ./build
HEDIR := ./helium

.PHONY: all helium

all: $(BUILDDIR) helium

$(BUILDDIR):
	mkdir ./build

helium:
	make -C $(HEDIR)

clean:
	rm -rf $(BUILDDIR)/*

