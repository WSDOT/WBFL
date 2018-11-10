REM use this script to install WBFL into %3
xcopy /y/d %WBFLDIR%\RegFreeCOM\%1\%2\WBFL*.lib %3\%1\%2\
xcopy /y/d %WBFLDIR%\RegFreeCOM\%1\%2\WBFL*.dll %3\%1\%2\
xcopy /y/d %WBFLDIR%\RegFreeCOM\%1\%2\MakeDocMap.exe %3\%1\%2\
xcopy /y/d %WBFLDIR%\deps\xerces-c_3_1.dll %3\%1\Release\
xcopy /y/d %WBFLDIR%\deps\xerces-c_3_1D.dll %3\%1\Debug\


