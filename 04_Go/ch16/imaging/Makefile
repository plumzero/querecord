
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

PROJECTNAME = imaging

MODULENAME = imaging.com


### do

.PHONY: all

all: deps clean build

deps:
	@if [ ! -e go.mod ]; then	     \
		$(GO-MOD) init $(MODULENAME);   \
	fi
	
	@$(GO-GET) github.com/disintegration/imaging@v1.6.2

clean:
	@for exefile in $(EXEFILES); do $(RM) $$exefile ; done;

build:
	@for gofile in $(GOFILES); do $(GO-BUILD) $$gofile; done;
