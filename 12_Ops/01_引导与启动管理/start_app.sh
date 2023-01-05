#!/bin/sh

echo "start app ..."

echo "runlevel: " `runlevel`

su - lumian -c 'LD_LIBRARY_PATH=/path/to/lib:$LD_LIBRARY_PATH /path/to/app &'
