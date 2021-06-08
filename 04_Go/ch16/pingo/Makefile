ENTERPATH?=..

include $(ENTERPATH)/mk/common.mk
include $(ENTERPATH)/mk/pingo.mk

.PHONY: all

all: deps clean build

deps:
	@if [ ! -e go.mod ]; then	     \
		$(GO-MOD) init $(MODULENAME);   \
	fi
	
	@$(GO-GET) github.com/dullgiulio/pingo

clean:
	@for exefile in $(EXEFILES); do $(RM) $$exefile ; done;

build: exe pin1 pin2

exe:
	@$(GO-BUILD) -o main

pin1:
	@cd plugins/$(PIN_HELLO) && $(GO-BUILD) && cd -;

pin2:
	@cd plugins/$(PIN_WORLD) && $(GO-BUILD) && cd -;
