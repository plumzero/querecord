
include $(MINIAPP)/mk/common.mk

.PHONY: all

all: clean build

build:
	@for gofile in $(GOFILES); do $(GO-BUILD) $$gofile; done;

clean:
	@for exefile in $(EXEFILES); do $(RM) $$exefile ; done;
