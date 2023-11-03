REM use this script to install WBFL into %3
REM 
REM To install WBFL
REM 1) In Solution Explorer, right click on a project that depends on WBFL and select Properties
REM 2) Select Custom Build Step > General
REM 3) In "Command Line", enter $(WBFLDIR)\InstallWBFL.bat $(PlatformName) $(ConfigurationName) $(OutDir)
REM 4) In "Description", enter "Installing WBFL"
REM 5) In "Outputs", enter $(OutDir)WBFL*.dll
REM
REM The output directory $(OutDir) should be $(SolutionDir)$(Platform)\$(Configuraion)\
REM

xcopy /y/d %ARPDIR%\WBFL\RegFreeCOM\%1\%2\WBFL*.lib %3
xcopy /y/d %ARPDIR%\WBFL\RegFreeCOM\%1\%2\WBFL*.dll %3
xcopy /y/d %ARPDIR%\WBFL\RegFreeCOM\%1\%2\MakeDocMap.exe %3

xcopy /y/d %ARPDIR%\WBFL\packages\Microsoft.Web.WebView2.1.0.2088.41\runtimes\win-x64\native\WebView2Loader.dll %3

IF "%1" == "Win32" (
    IF "%2" == "Release" (
   	xcopy /y/d %ARPDIR%\WBFL\Apache\XERCESCPKG-31-X86-VC100\bin\xerces-c_3_1.dll %3 
	) ELSE ( 
	xcopy /y/d %ARPDIR%\WBFL\Apache\XERCESCPKG-31-X86-VC100\bin\xerces-c_3_1D.dll %3 
	)
)

IF "%1" == "x64" (
   IF "%2" == "Release" (
   xcopy /y/d %ARPDIR%\WBFL\Apache\XERCESCPKG-31-X64-VC100\bin\xerces-c_3_1.dll %3 
   ) ELSE (
   xcopy /y/d %ARPDIR%\WBFL\Apache\XERCESCPKG-31-X64-VC100\bin\xerces-c_3_1D.dll %3 
   )
)

