
@echo off

if "%1" == "1" (echo is one) else (echo is not one)
ping 127.0.0.1 -n 2 > nul
cls

REM & means pipe in Windows bat
REM write the statement like this
if "%1" == "1" (
	if "%2" == "2" (
		hostname & ver
	) else (
		ver
	)
) else (
	hostname & ver & netstat -a
)
ping 127.0.0.1 -n 2 > nul
cls

REM check whether variable 'numServer' exist or not
set numServer=50
if defined numServer (echo Servers: %numServer%)

echo.
if /i "%1" == "a" (echo A) else (echo is not A)


@echo on
@pause