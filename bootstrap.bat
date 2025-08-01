@echo off
setlocal enabledelayedexpansion

:: --- Configuration ---
set "MSYS2_DIR=C:\msys64"
set "MSYS2_INSTALLER_URL=https://github.com/msys2/msys2-installer/releases/download/2025-06-22/msys2-x86_64-20250622.exe"
set "MSYS2_INSTALLER=msys2-x86_64-20250622.exe"
set "CURRENT_DIR=%~dp0"

:: --- Install MSYS2 if Needed ---
if exist "%MSYS2_DIR%\usr\bin\bash.exe" (
    echo MSYS2 already installed.
) else (
    echo MSYS2 not found. Downloading installer...
    curl -L -o "%MSYS2_INSTALLER%" "%MSYS2_INSTALLER_URL%"
    echo Running MSYS2 installer...
    start /wait "" "%MSYS2_INSTALLER%" --root "%MSYS2_DIR%" --scriptlet

    if not exist "%MSYS2_DIR%\usr\bin\bash.exe" (
        echo Failed to install MSYS2. Exiting.
        exit /b 1
    )
)

pause