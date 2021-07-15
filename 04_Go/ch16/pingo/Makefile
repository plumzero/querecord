
### common

GO ?= go
GO-BUILD = go build
GO-GET = go get -u
GO-FMT = go fmt
GO-MOD = go mod

RM ?= rm -rf

GOFILES := $(shell find . -name "*.go")
EXEFILES := $(shell find . -type f -perm /u=x,g=x,o=x)


### special

PROJECTNAME = pingo

MODULENAME = pingotest.com

PIN_HELLO = hello
PIN_WORLD = world


### do

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
