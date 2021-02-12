
@echo off

if "%1" == "" (
	echo Error: No parameter passed with script!
	goto EXIT
)

REM sub program
if "%1" == "1" goto SUBROUTINE1
if "%1" == "2" goto SUBROUTINE2
if "%1" == "3" goto SUBROUTINE3
if "%1" == "4" goto PROCESS
goto EXIT

:SUBROUTINE1
echo In subroutine1
goto EXIT

:SUBROUTINE2
echo In subroutine2
goto EXIT

:SUBROUTINE3
echo In subroutine3
goto EXIT

:PROCESS
cls
call echo.bat
@echo off
cls
echo return original script
goto EXIT

:EXIT
@echo on
@pause