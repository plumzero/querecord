#!/usr/bin/env make

.PHONY: deps all clean

deps:
	@if [ ! -e go.mod ]; then	   \
		go mod init miniapp.com;   \
	fi
	@go get -u github.com/gin-gonic/gin@v1.7.2



all:
	$(MAKE) -C 01_gin

clean:
	$(MAKE) -C 01_gin clean
