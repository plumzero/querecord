
@echo off

set /a theTotal = 18 + 2
echo %theTotal%
set /a theTotal = 18 * 2
echo %theTotal%
set /a theTotal = 18 / 2
echo %theTotal%
set /a theTotal += 1
echo %theTotal%
set /a theTotal = 2 * 2 * 2
echo %theTotal%
ping 127.0.0.1 -n 3 > nul

@echo on
@pause