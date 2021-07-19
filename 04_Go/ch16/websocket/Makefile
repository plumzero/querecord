
### common

GO-GET = go get -u
GO-MOD = go mod

### do

.PHONY: all

all: deps clean build

deps:
	@if [ ! -e go.mod ]; then	     \
		$(GO-MOD) init t-websocket.com;   \
	fi
	
	@$(GO-GET) github.com/gorilla/websocket

clean:
	$(MAKE) -C echo clean
	$(MAKE) -C chat clean

build:
	$(MAKE) -C echo build
	$(MAKE) -C chat build
