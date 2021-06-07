#!/usr/bin/env make

export THISPATH=$(PWD)

include $(THISPATH)/mk/common.mk

.PHONY: all

all: deps clean build

deps:
	$(MAKE) -C gin deps

clean:
	$(MAKE) -C gin clean

build:
	$(MAKE) -C gin build
