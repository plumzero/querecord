#!/usr/bin/env make

TOPDIR = `pwd`

BINDIR = $(TOPDIR)/bin
PKGDIR = $(TOPDIR)/pkg
SRCDIR = $(TOPDIR)/src

EXE = indicatordata
PLUGIN_1ST = hello
PLUGIN_2ND = world

all: clean build install

clean:
	@if [ ! -e $(BINDIR)/plugins ]; then \
		mkdir $(BINDIR)/plugins;	\
	fi
	@rm -rf $(BINDIR)/plugins/*
	@rm -rf $(BINDIR)/$(EXE)

build: exe pin1 pin2

install: install_exe install_pin1 install_pin2

.PHONY: all clean build install

# ---------- 可执行程序 ---------- #

exe:
	@cd $(SRCDIR) && go build -o $(EXE) && cd -;
	@echo $(EXE) "built"

install_exe:
	@mv $(SRCDIR)/$(EXE) $(BINDIR)/
	@echo $(EXE) "installed"


# ---------- 一号插件 ---------- #

pin1:
	@cd $(SRCDIR)/plugins/$(PLUGIN_1ST) && go build && cd -;
	@echo $(PLUGIN_1ST) "built"

install_pin1:
	@mv $(SRCDIR)/plugins/$(PLUGIN_1ST)/$(PLUGIN_1ST) $(BINDIR)/plugins/
	@echo $(PLUGIN_1ST) "installed"


# ---------- 二号插件 ---------- #

pin2:
	@cd $(SRCDIR)/plugins/$(PLUGIN_2ND) && go build && cd -;
	@echo $(PLUGIN_2ND) "built"

install_pin2:
	@mv $(SRCDIR)/plugins/$(PLUGIN_2ND)/$(PLUGIN_2ND) $(BINDIR)/plugins/
	@echo $(PLUGIN_2ND) "installed"
