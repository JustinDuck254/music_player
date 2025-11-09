@echo off
REM Music Player - Quick Launch Batch File
REM Double-click to build and run automatically

cd /d "%~dp0"
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "quick-run.ps1" -Mode buildrun
pause
