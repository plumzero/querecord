
@echo off
REM the input is an absolute file path
REM e.g. 	filexist.bat C:\Windows\System32\drivers\en-US\scsiport.sys.mui

if "%1" == "" (
	echo "input an absolute file path"
	goto EXIT
)

if "%OS%" == "Windows_NT" (SETLOCAL)

if exist "%1" (
	echo file exist
) else (
	echo file not exist
	goto EXIT
)

REM 	d Drive			 	p Path
REM 	n NameOfFile 		x eXtention
set DIRNAME=%~dp1
set FILENAME=%~nx1

echo %DIRNAME%
echo %FILENAME%

if "%OS%" == "Windows_NT" (ENDLOCAL)

:EXIT
@echo on
@pause