
### common

GO ?= go
GO-BUILD = go build
GO-GET = go get -u
GO-FMT = go fmt
GO-MOD = go mod
GO-BUILD-TEST = go test -v

RM ?= rm -rf

GOFILES := $(shell find . -name "*.go")
EXEFILES := $(shell find . -type f -perm /u=x,g=x,o=x)


### special

PROJECTNAME = testify

MODULENAME = testifytest.com


### do

.PHONY: all

all: deps clean build

deps:
	@if [ ! -e go.mod ]; then	     \
		$(GO-MOD) init $(MODULENAME);   \
	fi
	
	@$(GO-GET) github.com/stretchr/testify@v1.7.0

clean:
	@for exefile in $(EXEFILES); do $(RM) $$exefile ; done;

build:
	@for gofile in $(GOFILES); 	\
	do	\
		$(GO-BUILD-TEST) -o `echo $$gofile | sed -e 's/\.go//g'` -c $$gofile;	\
	done;
