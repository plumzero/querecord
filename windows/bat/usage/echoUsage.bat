
@echo off

echo.
echo Invalid Command Line Argument
echo.
echo Usage Rules:
echo pushcopy [Destination Path] [OS]
echo where [destination] is the drive letter and path (such as Z:)
echo       Do not add a trailing backslash (\) to the destination path. 
echo [OS]    	= OS family
echo WIN732		= Microsoft Windows 7* 32 bit
echo WIN7X64		= Microsoft Windows 7* x64
echo WS08R2X64	= Microsoft Windows Server 2008 R2* x64
echo WIN832         = Microsoft Windows 8 Client* 32 bit
echo WIN8X64        = Microsoft Windows 8 Client and Server* x64
echo WIN8.132         = Microsoft Windows 8.1 Client* 32 bit
echo WIN8.1X64        = Microsoft Windows 8.1 Client and Server* x64

echo.

@echo on
@pause