
@echo off

REM in the current directories

REM count the total number of files and directories
dir /B /A | find /V /C ""

REM count the total number of files, not include directories
dir /B /A:-D | find /V /C ""

REM count the total number of directories, not include files
dir /B /A:D | find /V /C ""

@echo on
@pause