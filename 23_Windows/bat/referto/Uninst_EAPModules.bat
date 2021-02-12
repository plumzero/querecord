PUSHD .
@cd /D "%~dp0"
@setlocal
@set logfile="%temp%\Uninstall_EAP_Modules.log"
@echo "***************************************" >> %logfile%
@echo "[%date% %time%] STARTING EAP MODULE UNINSTALLATIONS" >> %logfile%
@echo [%date% %time%] START MsiExec.exe /X{64BF0187-F3D2-498B-99EA-163AF9AE6EC9} /qn >> %logfile%
@MsiExec.exe /X{64BF0187-F3D2-498B-99EA-163AF9AE6EC9} /qn >> %logfile% 2>&1
if errorlevel 0 rmdir /s /q "C:\Program Files (x86)\Cisco\Cisco EAP-FAST Module" >> %logfile%
@if errorlevel 0 echo MsiExec.exe /X{64BF0187-F3D2-498B-99EA-163AF9AE6EC9} /qn exited with errorlevel=%errorlevel% >> %logfile%
@echo [%date% %time%] END   MsiExec.exe /X{64BF0187-F3D2-498B-99EA-163AF9AE6EC9} /qn >> %logfile%
@echo "=======================================" >> %logfile%
@echo [%date% %time%] START MsiExec.exe /X{51C7AD07-C3F6-4635-8E8A-231306D810FE} /qn >> %logfile%
@MsiExec.exe /X{51C7AD07-C3F6-4635-8E8A-231306D810FE} /qn >> %logfile% 2>&1
if errorlevel 0 rmdir /s /q "C:\Program Files (x86)\Cisco\Cisco LEAP Module" >> %logfile%
@if errorlevel 0 echo MsiExec.exe /X{51C7AD07-C3F6-4635-8E8A-231306D810FE} /qn exited with errorlevel=%errorlevel% >> %logfile%
@echo [%date% %time%] END   MsiExec.exe /X{51C7AD07-C3F6-4635-8E8A-231306D810FE} /qn >> %logfile%
@echo "=======================================" >> %logfile%
@echo [%date% %time%] START MsiExec.exe /X{ED5776D5-59B4-46B7-AF81-5F2D94D7C640} /qn >> %logfile%
@MsiExec.exe /X{ED5776D5-59B4-46B7-AF81-5F2D94D7C640} /qn >> %logfile% 2>&1
if errorlevel 0 rmdir /s /q "C:\Program Files (x86)\Cisco\Cisco PEAP Module" >> %logfile%
@if errorlevel 0 echo MsiExec.exe /X{ED5776D5-59B4-46B7-AF81-5F2D94D7C640} /qn exited with errorlevel=%errorlevel% >> %logfile%
@echo [%date% %time%] END   MsiExec.exe /X{ED5776D5-59B4-46B7-AF81-5F2D94D7C640} /qn >> %logfile%
@echo "=======================================" >> %logfile%
@echo "" >> %logfile%
@echo "***************************************" >> %logfile%
@endlocal
POPD
