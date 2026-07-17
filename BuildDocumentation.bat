@echo off
setlocal enabledelayedexpansion

rem Builds doxygen documentation for every *.dox file found under the WBFL tree.
rem Doxyfiles use paths relative to their own directory, so we cd into each
rem Doxyfile's folder before invoking doxygen.

set SCRIPT_DIR=%~dp0
set ERROR_COUNT=0

where doxygen >nul 2>nul
if errorlevel 1 (
    echo ERROR: doxygen was not found on the PATH.
    exit /b 1
)

for /r "%SCRIPT_DIR%" %%F in (*.dox) do (
    echo ============================================================
    echo Building: %%F
    echo ============================================================
    pushd "%%~dpF"
    doxygen "%%~nxF"
    if errorlevel 1 (
        echo ERROR: doxygen failed for %%F
        set /a ERROR_COUNT+=1
    )
    popd
)

echo ============================================================
if %ERROR_COUNT% equ 0 (
    echo All documentation built successfully.
) else (
    echo Completed with %ERROR_COUNT% failure^(s^).
)
echo ============================================================

endlocal
exit /b %ERROR_COUNT%
