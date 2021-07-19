
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

all: clean build

clean:
	@for exefile in $(EXEFILES); do $(RM) $$exefile ; done;

build: $(GOFILES)
	@$(GO-BUILD) -o chatserver $^
