REM use this script to install image files for reports contained in WBFL project to %1
REM 
REM To install WBFL report images
REM 1) In Solution Explorer, right click on a project that depends on report images and select Properties
REM 2) Select Custom Build Step > General
REM 3) In "Command Line", enter $(WBFLDIR)\InstallWBFL_ReportImages.bat Path_To_Images_Folder
REM 4) In "Description", enter "Installing WBFL Report Images"
REM 5) In "Outputs", enter Path_To_Images_Folder\*.*
REM

xcopy /y/d/i %ARPDIR%\WBFL\Stability\images\*.png %1\WBFLStability
