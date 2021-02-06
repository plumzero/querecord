
@echo off
title Current Environment Variable
set
ping 127.0.0.1 -n 2 > nul
cls

title Set a New Environment Variable
REM set it
set variable_name=variable_value
set working=%cd%
set value=5
set string="Hello World"
REM print it
echo %variable_name%
echo %working%
echo %value%
echo %string%
REM free it
set variable_name=
set working=
set value=
set string=
ping 127.0.0.1 -n 2 > nul
cls

if not "%OS%"=="Windows_NT" goto :EXIT
if "%1"=="" (set INFO=echo && set SEXIT=I) else (set INFO=rem && set SEXIT=0)
title Script Infomation
%INFO% **************************************
%INFO% Script: SystemInfo. bat
%INFO% Creation Date: 1/4/2019
%INFO% Last Modified: 1/4/2019
%INFO% Author: LB
%INFO% E-mail: libeioando@gmail.com
%INFO% Description: SET useage
%INFO% **************************************
%INFO% Files: Stores output in C
%INFO% **************************************
ping 127.0.0.1 -n 2 > nul
cls

REM localize the variable
set sysCount=0
set deviceCount=0
REM start localization
SETLOCAL
set sysCount=5
set deviceCount=5
echo Local count: %sysCount% system edits ^& %deviceCount% dev ice checks
ENDLOCAL
echo Count: %sysCount% system edits ^& %deviceCount% dev ice checks
ping 127.0.0.1 -n 2 > nul

if "%SEXIT%"=="I" goto :EXIT

title Configure Scheduling...

:EXIT
ping 127.0.0.1 -n 2 > nul
cls
color 7

@echo on
@pause