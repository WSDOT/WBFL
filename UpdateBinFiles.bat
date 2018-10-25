REM - Script to copy the various binary files to the "bin" folder
REM - Run this script just prior to tagging the repository with ready-x-y-z-b

REM - Binary Files for basic development

set BINTARGET=bin

COPY "RegFreeCOM\Win32\Release\WBFL*.dll"	"%BINTARGET%\Libraries\Win32\"
COPY "RegFreeCOM\Win32\Release\WBFL*.lib"	"%BINTARGET%\Lib\Win32\"

COPY "RegFreeCOM\x64\Release\WBFL*.dll"	"%BINTARGET%\Libraries\x64\"
COPY "RegFreeCOM\x64\Release\WBFL*.lib"	"%BINTARGET%\Lib\x64\"

COPY License.rtf 			"%BINTARGET%"

REM - Help files and documentation

COPY RegFreeCOM\*.chm			"%BINTARGET%\App\"
COPY License.txt			"%BINTARGET%\App\"
