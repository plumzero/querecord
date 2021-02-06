
@echo off

set Flag=0

set Normal=YES

set Magic=
set Equip=
set Field=

set Trap=
set Counter=

set Monster=
set Effect=

:opts
if "a%1" == "a" (goto endopt)

if /I "%1" == "magic" 		set Magic=YES
if /I "%1" == "equip"		set Equip=YES
if /I "%1" == "field"		set Field=YES

if /I "%1" == "trap"		set Trap=YES
if /I "%1" == "Counter"		set Counter=YES

if /I "%1" == "Monster"		set Monster=YES
if /I "%1" == "Effect"		set Effect=YES

REM echo ... "%1"

shift
goto opts
:endopt

if not "%Magic%"    == "" (set /A Flag+=1)
if not "%Trap%"     == "" (set /A Flag+=1)
if not "%Monster%"  == "" (set /A Flag+=1)

if "%Flag%" == "0" (echo Error Parameters, exit & goto EXIT)
if not "%Flag%" == "1" (echo Chaos %Flag%, exit & goto EXIT)

if "%Magic%" == "YES" (
	if "%Equip%" == "YES" (
		echo equip magic
	) else if "%Field%" == "YES" (
		echo field magic
	) else (
		echo normal magic
	)
)

if "%Trap%" == "YES" (
	if "%Counter%" == "YES" (
		echo counter trap
	) else (
		echo normal trap
	)
)

if "%Monster%" == "YES" (
	if "%Effect%" == "YES" (
		echo effect monster
	) else (
		echo normal monster
	)
)

:EXIT
@echo on
@pause