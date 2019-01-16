REM use this script to install WBFL into %3
xcopy /y/d %WBFLDIR%\RegFreeCOM\%1\%2\WBFL*.lib %3\%1\%2\
xcopy /y/d %WBFLDIR%\RegFreeCOM\%1\%2\WBFL*.dll %3\%1\%2\
xcopy /y/d %WBFLDIR%\RegFreeCOM\%1\%2\MakeDocMap.exe %3\%1\%2\
xcopy /y/d %WBFLDIR%\Apache\XERCESCPKG-31-X86-VC100\bin\xerces-c_3_1.dll %3\Win32\Release\
xcopy /y/d %WBFLDIR%\Apache\XERCESCPKG-31-X86-VC100\bin\xerces-c_3_1D.dll %3\Win32\Debug\
xcopy /y/d %WBFLDIR%\Apache\XERCESCPKG-31-X64-VC100\bin\xerces-c_3_1.dll %3\x64\Release\
xcopy /y/d %WBFLDIR%\Apache\XERCESCPKG-31-X64-VC100\bin\xerces-c_3_1D.dll %3\x64\Debug\


