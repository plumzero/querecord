
@echo off

if %1 == "" (
	echo "specify the destination string to search"
	goto :Exit
)

title search the string "%1"

REM show LINE and case-nonsensitive
for /R "%CD%" %%B in (*) do (
	findstr /N /I /A:71 "\<%1\>" "%%B" && echo %%B
)

:Exit
title  %ComSpec%
@echo on
@pause