@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by LBAMVIEWER.HPJ. >"hlp\LBAMViewer.hm"
echo. >>"hlp\LBAMViewer.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\LBAMViewer.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\LBAMViewer.hm"
echo. >>"hlp\LBAMViewer.hm"
echo // Prompts (IDP_*) >>"hlp\LBAMViewer.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\LBAMViewer.hm"
echo. >>"hlp\LBAMViewer.hm"
echo // Resources (IDR_*) >>"hlp\LBAMViewer.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\LBAMViewer.hm"
echo. >>"hlp\LBAMViewer.hm"
echo // Dialogs (IDD_*) >>"hlp\LBAMViewer.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\LBAMViewer.hm"
echo. >>"hlp\LBAMViewer.hm"
echo // Frame Controls (IDW_*) >>"hlp\LBAMViewer.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\LBAMViewer.hm"
REM -- Make help for Project LBAMVIEWER


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\LBAMViewer.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\LBAMViewer.hlp" goto :Error
if not exist "hlp\LBAMViewer.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\LBAMViewer.hlp" Debug
if exist Debug\nul copy "hlp\LBAMViewer.cnt" Debug
if exist Release\nul copy "hlp\LBAMViewer.hlp" Release
if exist Release\nul copy "hlp\LBAMViewer.cnt" Release
echo.
goto :done

:Error
echo hlp\LBAMViewer.hpj(1) : error: Problem encountered creating help file

:done
echo.
