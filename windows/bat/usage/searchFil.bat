
@echo off
REM Function:	search a specified FileName in the current directory tree
REM Usage:		searchFil.bat FileName
REM Attention:	run the script with appropriate permissions

REM 中文说明（部分计算机上不兼容中文注释，所以运行之前需要删除）
REM bat 脚本到目前为止还没有发现怎么使用函数，所以暂时还无法使用递归来进行目录的搜索
REM 不过就算可以使用递归，但是好像还没有发现对栈的处理操作（如类似于pop push等），所以就算对子目录处理完毕后再返回，仍然是要回到父目录下的第一个目录
REM 总之，bat 脚本太不方便了
REM 有了 Pushed Poped

if "%1" == "" (echo parameter error & goto EXIT)

title search the file "%1"

for /R "%CD%" %%B in (*) do (
	if /I "%%~nxB" == "%1" (
		echo %%B
	)
)

:EXIT
title  %ComSpec%
@echo on
@pause