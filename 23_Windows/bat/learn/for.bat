
@echo off

REM list the number with a certain convention
for /L %%B in (0, 2, 10) do (
	echo %%B
)
for /L %%B in (10, -2, 0) do (
	echo %%B
)
ping 127.0.0.1 -n 2 > nul
cls

REM list all *.bat filename in this directory
for %%B in (%CD%\*.bat %CD%\*.txt) do (
	echo %%B
)
ping 127.0.0.1 -n 2 > nul
cls

REM list all sub directory in %SystemRoot%
for /D %%B in (%SystemRoot%\* %SystemRoot%\System32\*) do (
	echo %%B
)
ping 127.0.0.1 -n 2 > nul
cls

REM list all *.txt in the subdirectory of %SystemRoot%. Do not include the two-level subdirectory of subdirectories
for /D %%B in (%SystemRoot%\*) do (
	for %%C in ("%%B\*.txt") do (
		echo %%C
	)
)
ping 127.0.0.1 -n 2 > nul
cls

REM traverse the directory tree of %SystemRoot% and select the *.log into the fileSet and echo it 
for /R "%SystemRoot%\debug" %%B in (*.log) do (
	echo %%B
)
ping 127.0.0.1 -n 2 > nul
cls

REM count the *.tmp in %Temp% tree
set count=0
for /R "%Temp%" %%B in (*.tmp) do (
	set /a count+=1
)
echo total tmp file is %count%
set count=
ping 127.0.0.1 -n 2 > nul
cls

cd ..
cd tmp
for /R "%CD%" %%B in ("*.txt" "*.people" "*.file" "*.poem") do (
	echo %%B
	for /F "usebackq tokens=1-5  delims=,.; " %%a in ("%%B") do (
		echo %%a %%b %%c %%d %%e
	)
)
ping 127.0.0.1 -n 2 > nul
cls

REM search string "the" in %CD% tree
for /R "%CD%" %%B in ("*.txt" "*.people" "*.file" "*.poem") do (
	echo %%B
	for /F "usebackq tokens=*" %%a in ("%%B") do (
		echo %%a | findstr /A:81 /I "the"
	)
)
ping 127.0.0.1 -n 2 > nul
cls

set myStr="William Stanek Engineering Williams@adatum.com 3408"
for /F "tokens=1-5" %%A in (%myStr%) do (
	echo Name: %%A %%B 
	echo Depart: %%C 
	echo E-mail: %%D
	echo Ext: %%E
)
echo.
for /F "skip=3 eol=; tokens=3-5" %%C in (%myStr%) do (
	echo Depart: %%C
	echo E-mail: %%D
	echo Ext: %%E
)
ping 127.0.0.1 -n 2 > nul

@echo on
@pause