
### common

GO-GET = go get -u
GO-MOD = go mod

### do

.PHONY: all

all: deps clean build

deps:
	@if [ ! -e go.mod ]; then	     \
		$(GO-MOD) init t-redis.com;   \
	fi
	
	@$(GO-GET) github.com/go-redis/redis/v8

clean:
	$(MAKE) -C String clean

build:
	$(MAKE) -C String build
