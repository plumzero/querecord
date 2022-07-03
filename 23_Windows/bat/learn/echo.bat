
@echo off
color 81

title Script Information 
echo *******************************************
echo Script: SysInfo.bat
echo Creation Data: 2019/1/3
echo Last Modified: 2019/1/3
echo Author: SC
echo E-mail: shencheng@email.com
echo *******************************************
echo Description: use ECHO control the display
echo *******************************************

:: *******************************************
:: Script: SysInfo.bat
:: Creation Data: 2019/1/3
:: Last Modified: 2019/1/3
:: Author: SC
:: E-mail: shencheng@email.com
:: *******************************************
:: Description: Displays system configuration information
:: 				including system name. IP configuration
:: 				and Windows version
:: *******************************************
:: Files: Stores output in F:\arrange\windows\tmp\current-sys.txt.
:: *******************************************


REM sleep for 5 seconds
ping 127.0.0.1 -n 6 > nul

echo.
title System Information
systeminfo

@echo on
