
### common

GO-GET = go get -u
GO-MOD = go mod

### do

.PHONY: all

all: deps clean build

deps:
	@if [ ! -e go.mod ]; then	     \
		$(GO-MOD) init pgt.com;   \
	fi
	
	@$(GO-GET) github.com/go-pg/pg/v10@v10.9.0

clean:
	@for exefile in $(EXEFILES); do $(RM) $$exefile ; done;

build:
	@for gofile in $(GOFILES); do $(GO-BUILD) $$gofile; done;
