@echo off
cd ..\..\build\release\install-root\tests
set QTDIR=C:\Qt\5.10.0\msvc2017_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
set "success=true"
for /r "." %%a in (*.exe) do (
	echo "%%~fa"
	call "%%~fa"
	if errorlevel 1 (
      set "success=false"
	)
)
if "%success%" == "true" (
	exit /b 0
) else (
	exit /b 1
)