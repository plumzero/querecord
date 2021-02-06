
@echo off
color 81

title Script Information 
echo *******************************************
echo Script: helloworld.bat
echo Creation Data: 2020/12/05
echo Last Modified: 2020/12/05
echo Author: libeio
echo E-mail: ytmrlimei@163.com
echo *******************************************
echo Description: display system information
echo *******************************************

REM sleep for 5 seconds
ping 127.0.0.1 -n 6 > nul

echo.
title System Information
systeminfo

@echo on
