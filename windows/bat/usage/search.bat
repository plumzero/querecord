
@echo off

set para=%1
if %para% == "" (
	echo "specify the destination string to search"
	goto :Exit
)

REM show LINE and case-nonsensitive
for /R "%CD%" %%B in ("*.c" "*.h") do (
	echo %%B
	find /N /I "%para%" "%%B"
)
ping 127.0.0.1 -n 5 > nul
REM cls

REM show LINE and case-nonsensitive
REM too slowly to wait
for /R "%CD%" %%B in ("*.c" "*.h") do (
	echo %%B
	for /F "usebackq tokens=*" %%a in ("%%B") do (
		echo "%%a" | findstr /I /N /O "\<%para%\>"
	)
)
ping 127.0.0.1 -n 2 > nul

:Exit
@echo on
@pause