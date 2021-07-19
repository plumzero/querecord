
### common

GO ?= go
GO-BUILD = go build
GO-GET = go get -u
GO-FMT = go fmt
GO-MOD = go mod

RM ?= rm -rf

GOFILES := $(shell find . -name "*.go")
EXEFILES := $(shell find . -type f -perm /u=x,g=x,o=x)

### do

.PHONY: all

all: deps clean build

deps:
	@if [ ! -e go.mod ]; then	      \
		$(GO-MOD) init t-viper.com;   \
	fi
	
	@$(GO-GET) github.com/spf13/viper

clean:
	@for exefile in $(EXEFILES); do $(RM) $$exefile ; done;

build:
	@for gofile in $(GOFILES); do $(GO-BUILD) $$gofile; done;
