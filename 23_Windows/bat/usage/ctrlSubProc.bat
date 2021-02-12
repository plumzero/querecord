@echo off

if /I "%1" == "p" 		goto PathItem
if /I "%1" == "c"		goto CountItem
if /I "%1" == "d"		goto DeleteItem

goto Usage

:PathItem
title Show full path information 

for /D /R "%CD%" %%B in (*) do (
	if /I %%~nxB == temp (
		echo %%B
	)
)
goto EXIT

:CountItem
title Count number of Files(included directories)

for /D /R "%CD%" %%B in (*) do (
	if /I %%~nxB == temp (
		echo %%B
		if exist %%B (
			dir /B /A %%B | find /V /C ""
		)
	)
)
goto EXIT

:DeleteItem
title Simple cleanup...

for /D /R "%CD%" %%B in (*) do (
	if /I %%~nxB == temp (
		echo cleaning %%B ...
		del /F /S /Q %%B\*.tmp
		del /F /S /Q %%B\*.TMP
		del /F /S /Q %%B\*._mp
		del /F /S /Q %%B\*.log
		del /F /S /Q %%B\*.gid
		del /F /S /Q %%B\*.chk
		del /F /S /Q %%B\*.old
		del /F /S /Q %%B\*.bak
		del /F /S /Q %%B\*.cvr
		del /F /S /Q %%B\*.zip
		del /F /S /Q %%B\*.xml
		del /F /S /Q %%B\*.jpg
		del /F /S /Q %%B\*.png
		del /F /S /Q %%B\*.gif
		del /F /S /Q %%B\*.etl
		del /F /S /Q %%B\*.ico
		del /F /S /Q %%B\*.gz
		del /F /S /Q %%B\*.txt
		del /F /S /Q %%B\*.html
		del /F /S /Q %%B\*.xpi
		del /F /S /Q %%B\*.sqm
		del /F /S /Q %%B\*.fcg
		del /F /S /Q %%B\*.ref
		del /F /S /Q %%B\systray_temp_icon*
		del /F /S /Q %%B\tmpaddon*
		del /F /S /Q %%B\cdstmp*
		rd /S /Q %%B\rust_mozprofile.*
		rd /S /Q %%B\notifu-notifier*
		rd /S /Q %%B\{*}
		rd /S /Q %%B\ppcrlui_*
	)
)
goto EXIT


:Usage
echo.
echo Valid Command Line Argument
echo.
echo Usage Rules:
echo P[p]		= Show full path information
echo C[c]		= Count number of Files(included directories)
echo D[d]		= Simple clean up

echo.

:EXIT
@echo on
@pause
