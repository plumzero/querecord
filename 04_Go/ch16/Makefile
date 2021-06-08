#!/usr/bin/env make

export ENTERPATH=$(PWD)

include $(ENTERPATH)/mk/common.mk

.PHONY: all

all: deps clean build

deps:
	$(MAKE) -C gin deps
	$(MAKE) -C pingo deps

clean:
	$(MAKE) -C gin clean
	$(MAKE) -C pingo clean

build:
	$(MAKE) -C gin build
	$(MAKE) -C pingo build
