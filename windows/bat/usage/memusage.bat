
@echo off

if "%1" == "" (echo Error: please enter Process ID to track) & (goto EXIT)

REM tasklist /FI "pid eq %1"
REM timeout /t 600
REM tasklist /FI "pid eq %1"

set cnt=0
:loop
	tasklist /FI "pid eq %1"
	
	set /a cnt += 1
	if "%cnt%" gtr "5" (goto EXIT)
	
	ping 127.0.0.1 -n 10 > nul
goto loop

:EXIT
@echo on
@pause